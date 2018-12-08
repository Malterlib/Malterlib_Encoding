// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
	namespace NPrivate
	{
		void fg_GenerateJSONValue(NStr::CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator);

		void fg_AddPrefix(NStr::CStr &o_String, mint _Depth, ch8 const *_pPrettySeparator)
		{
			for (mint i = 0; i < _Depth; ++i)
				o_String += _pPrettySeparator;
		}

		void fg_GenerateJSONString(NStr::CStr &o_String, NStr::CStr const &_Value)
		{
			using namespace NStr;

			o_String += "\"";

			ch8 const *pParse = _Value;

			while (*pParse)
			{
				auto UnsignedChar = fg_Unsigned(*pParse);
				switch (UnsignedChar)
				{
				case '\"':
					o_String += "\\\"";
					break;
				case '\\':
					o_String += "\\\\";
					break;
				case 0x08:
					o_String += "\\b";
					break;
				case 0x0C:
					o_String += "\\f";
					break;
				case 0x0A:
					o_String += "\\n";
					break;
				case 0x0D:
					o_String += "\\r";
					break;
				case 0x09:
					o_String += "\\t";
					break;
				default:
					if (UnsignedChar < 32)
						o_String += CStr::CFormat("\\u{nfh,sf0,sj4}") << UnsignedChar; // Control character, add as hex
					else
						o_String.f_AddChar(*pParse);
					break;
				}
				++pParse;
			}

			o_String += "\"";
		}

		void fg_GenerateJSONObject(NStr::CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
		{
			auto iChild = _Value.f_Object().f_OrderedIterator();
			if (!iChild)
			{
				// Empty object
				o_String += "{}";
				return;
			}

			if (_pPrettySeparator)
				o_String += "{\n";
			else
				o_String += "{";

			while (iChild)
			{
				auto &Child = *iChild;
				++iChild;
				if (_pPrettySeparator)
					fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
				fg_GenerateJSONString(o_String, Child.f_Name());
				if (_pPrettySeparator)
					o_String += ": ";
				else
					o_String += ":";
				fg_GenerateJSONValue(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator);
				if (_pPrettySeparator)
				{
					if (iChild)
						o_String += ",\n";
					else
						o_String += "\n";
				}
				else if (iChild)
					o_String += ",";
			}
			if (_pPrettySeparator)
				fg_AddPrefix(o_String, _Depth, _pPrettySeparator);
			o_String += "}";
		}

		void fg_GenerateJSONArray(NStr::CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
		{
			auto iChild = _Value.f_Array().f_GetIterator();
			if (!iChild)
			{
				// Empty array
				o_String += "[]";
				return;
			}

			if (_pPrettySeparator)
				o_String += "[\n";
			else
				o_String += "[";
			while (iChild)
			{
				auto &Child = *iChild;
				++iChild;
				if (_pPrettySeparator)
					fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
				fg_GenerateJSONValue(o_String, Child, _Depth + 1, _pPrettySeparator);
				if (_pPrettySeparator)
				{
					if (iChild)
						o_String += ",\n";
					else
						o_String += "\n";
				}
				else if (iChild)
					o_String += ",";
			}
			if (_pPrettySeparator)
				fg_AddPrefix(o_String, _Depth, _pPrettySeparator);
			o_String += "]";
		}

		void fg_GenerateJSONValue(NStr::CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
		{
			using namespace NStr;

			auto &JSONValue = _Value;

			switch (JSONValue.f_Type())
			{
			case EJSONType_String:
				fg_GenerateJSONString(o_String, JSONValue.f_String());
				break;
			case EJSONType_Integer:
				o_String += CStr::fs_ToStr(JSONValue.f_Integer());
				break;
			case EJSONType_Float:
				{
					auto &Float = JSONValue.f_Float();
					if (Float.f_IsInvalid())
						o_String += "null"; // QNaN, Inf etc is not representable in JSON
					else
						o_String += CStr::fs_ToStr(JSONValue.f_Float());
				}
				break;
			case EJSONType_Object:
				fg_GenerateJSONObject(o_String, _Value, _Depth, _pPrettySeparator);
				break;
			case EJSONType_Array:
				fg_GenerateJSONArray(o_String, _Value, _Depth, _pPrettySeparator);
				break;
			case EJSONType_Null:
				o_String += "null";
				break;
			case EJSONType_Boolean:
				if (JSONValue.f_Boolean())
					o_String += "true";
				else
					o_String += "false";
				break;
			default:
				DMibError("Invalid JSON type in value node");
			break;
			}
		}

		NStr::CStr fg_JSONGenerate(CJSON const &_JSON, ch8 const *_pPrettySeparator)
		{
			using namespace NStr;

			CStr Return;

			fg_GenerateJSONValue(Return, _JSON, 0, _pPrettySeparator);

			if (_pPrettySeparator)
				Return += "\n";

			return Return;
		}
	}
}
