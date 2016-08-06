// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/Storage/Variant>
#include <Mib/Storage/Indirection>
#include <Mib/Storage/Tuple>

#include "Malterlib_Encoding_JSON_InternalBase.h"

namespace NMib
{
	namespace NEncoding
	{
		enum EJSONType : uint8
		{
			EJSONType_Invalid = 0
			, EJSONType_Null
			, EJSONType_String
			, EJSONType_Integer
			, EJSONType_Float
			, EJSONType_Boolean
			, EJSONType_Object
			, EJSONType_Array
			, EJSONType_Max = 32
		};

		template <typename t_CJSONValue>
		class TCJSONObject;

		template <typename t_CParent>
		class TCJSONValue : public t_CParent
		{
		protected:
			using CValue = typename t_CParent::CValue;
		public:
			typedef TCJSONObject<CValue> CObject;
			typedef NContainer::TCVector<CValue> CArray;

			struct CKeyValue
			{
				NStr::CStr m_Key;
				CValue m_Value;
			};
			
			struct CKey
			{
				CKey();
				CKey(CKey &&_Other);
				NStr::CStr m_Key;
				inline_always CKeyValue operator = (CValue &&_Value) &&;
				inline_always CKeyValue operator = (TCInitializerList<CVoidTag> const &_Initializer) &&;
			private:
				CKey(CKey const &_Other);
			};
			
			template <typename tf_CType, TCDisableIfForbidden<tf_CType> * = nullptr>
			TCJSONValue(tf_CType &&_Type);
			TCJSONValue();
			TCJSONValue(TCJSONValue const &_Other);
			TCJSONValue(TCJSONValue &_Other);
			TCJSONValue(TCJSONValue &&_Other);
			TCJSONValue(TCJSONValue const &&_Other);
			TCJSONValue(EJSONType _Type);
			TCJSONValue(ch8 const *_pValue);
			TCJSONValue(TCInitializerList<CValue> const &_Init);
			TCJSONValue(TCInitializerList<CKeyValue> const &_Init);

			template <typename tf_CType>
			CValue &operator = (tf_CType &&_Value);
			CValue &operator = (TCJSONValue const &_Value);
			CValue &operator = (TCJSONValue &_Value);
			CValue &operator = (TCJSONValue &&_Value);
			CValue &operator = (pfp64 _Value);
			CValue &operator = (pfp32 _Value);
			CValue &operator = (fp32 _Value);
			CValue &operator = (bool _Value);
			CValue &operator = (EJSONType _Type);
			CValue &operator = (ch8 const *_pValue);

			bool operator == (TCJSONValue const &_Right) const;
			bool operator < (TCJSONValue const &_Right) const;

			EJSONType f_Type() const;
			void f_SetType(EJSONType _Type);

			bool f_IsValid() const;
			bool f_IsNull() const;
			bool f_IsString() const;
			bool f_IsInteger() const;
			bool f_IsFloat() const;
			bool f_IsBoolean() const;
			bool f_IsObject() const;
			bool f_IsArray() const;

			NStr::CStr const &f_String() const;
			NStr::CStr &f_String();
			int64 const &f_Integer() const;
			int64 &f_Integer();
			fp64 const &f_Float() const;
			fp64 &f_Float();
 			bool const &f_Boolean() const;
 			bool &f_Boolean();
			TCJSONObject<CValue> const &f_Object() const;
			TCJSONObject<CValue> &f_Object();
			NContainer::TCVector<CValue> const &f_Array() const;
			NContainer::TCVector<CValue> &f_Array();
			
			NStr::CStr f_AsString() const;
			int64 f_AsInteger() const;
			fp64 f_AsFloat() const;
 			bool f_AsBoolean() const;

			NStr::CStr f_AsString(NStr::CStr const &_Default) const;
			int64 f_AsInteger(int64 _Default) const;
			fp64 f_AsFloat(fp64 _Default) const;
 			bool f_AsBoolean(bool _Default) const;

			//
			// Object helpers
			// ==============
			CValue const *f_GetMember(NStr::CStr const &_Name) const;
			CValue *f_GetMember(NStr::CStr const &_Name);
			CValue const *f_GetMember(NStr::CStr const &_Name, EJSONType _Type) const;
			CValue *f_GetMember(NStr::CStr const &_Name, EJSONType _Type);
			CValue &operator [] (NStr::CStr const &_Name);
			CValue const &operator [] (NStr::CStr const &_Name) const;
			void f_RemoveMember(NStr::CStr const &_Name);

			//
			// Array helpers
			// =============
			mint f_GetLen() const;
			void f_SetLen(mint _Len);

			template <typename tf_CType>
			CValue &f_Insert(tf_CType &&_Value);
			CValue &f_Insert();
			CValue const &operator [] (mint _Index) const;
			CValue &operator [] (mint _Index);

			//
			// Formatting
			// ==============

			struct CFormatOptions
			{
				ch8 m_PrettySeparator[32] = "\t";
			};
			
			template <typename tf_COption>
			bool f_FormatParseOption(CFormatOptions &_Options, tf_COption &_Option) const;
			template <typename tf_CFormatInto, typename tf_CFormatOptions>
			void f_Format(tf_CFormatInto &o_FormatInto, tf_CFormatOptions const &_Options) const;

			//
			// Parsing/generating
			// ==============

			static TCJSONValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = NStr::CStr());
			NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t") const;
			
		protected:
			inline_always void fp_CheckType(EJSONType _Type) const;
			inline_always void fp_PromoteType(EJSONType _Type);
		};

		template <typename tf_CJSONValue>
		typename NContainer::TCLinkedList<NPrivate::TCObjectEntry<tf_CJSONValue>>::CIterator begin(TCJSONObject<tf_CJSONValue> &_JSONObject);
		template <typename tf_CJSONValue>
		NContainer::CIteratorEndSentinel end(TCJSONObject<tf_CJSONValue> &_JSONObject);
		template <typename tf_CJSONValue>
		typename NContainer::TCLinkedList<NPrivate::TCObjectEntry<tf_CJSONValue>>::CIteratorConst begin(TCJSONObject<tf_CJSONValue> const &_JSONObject);
		template <typename tf_CJSONValue>
		NContainer::CIteratorEndSentinel end(TCJSONObject<tf_CJSONValue> const &_JSONObject);
		
		template <typename t_CJSONValue>
		class TCJSONObject
		{
		public:
			typedef NPrivate::TCObjectEntry<t_CJSONValue> CObjectEntry;
		private:
			typedef typename NPrivate::CObjectEntryBase::CCompare CCompare;
			struct CLinkTraits : public NPrivate::CObjectEntryBase::CLinkTraits_mp_Link
			{
				typedef CObjectEntry CNode;
			};

			template <typename tf_CJSONValue>
			friend typename NContainer::TCLinkedList<NPrivate::TCObjectEntry<tf_CJSONValue>>::CIterator begin(TCJSONObject<tf_CJSONValue> &_JSONObject);
			template <typename tf_CJSONValue>
			friend typename NContainer::TCLinkedList<NPrivate::TCObjectEntry<tf_CJSONValue>>::CIteratorConst begin(TCJSONObject<tf_CJSONValue> const &_JSONObject);
			
		public:
			
			TCJSONObject();
			~TCJSONObject();
			TCJSONObject(TCJSONObject const &_Other);
			TCJSONObject(TCJSONObject &&_Other);

			bool operator == (TCJSONObject const &_Right) const;
			bool operator < (TCJSONObject const &_Right) const;

			t_CJSONValue const *f_GetMember(NStr::CStr const &_Name) const;
			t_CJSONValue *f_GetMember(NStr::CStr const &_Name);
			t_CJSONValue const *f_GetMember(NStr::CStr const &_Name, EJSONType _Type) const;
			t_CJSONValue *f_GetMember(NStr::CStr const &_Name, EJSONType _Type);
			t_CJSONValue &f_CreateMember(NStr::CStr const &_Name);
			void f_RemoveMember(NStr::CStr const &_Name);
			void f_RemoveMember(typename NContainer::TCLinkedList<CObjectEntry>::CIteratorConst &_Iterator);
			void f_RemoveMember(typename NContainer::TCLinkedList<CObjectEntry>::CIterator &_Iterator);
			void f_RemoveMember(typename NIntrusive::TCAVLTree<CLinkTraits, CCompare>::CIterator &_Iterator);

			typename NContainer::TCLinkedList<CObjectEntry>::CIteratorConst f_OrderedIterator() const;
			typename NContainer::TCLinkedList<CObjectEntry>::CIterator f_OrderedIterator();

			typename NIntrusive::TCAVLTree<CLinkTraits, CCompare>::CIterator f_SortedIterator() const;
			
			template <typename tf_CStream>
			void f_Feed(tf_CStream &_Stream) const;
			template <typename tf_CStream>
			void f_Consume(tf_CStream &_Stream);
			
		private:
			NContainer::TCLinkedList<CObjectEntry> mp_Objects;
			NIntrusive::TCAVLTree<CLinkTraits, CCompare> mp_ObjectTree;
		};
		
		using NContainer::operator==;
		
		template <typename tf_CJSONValue>
		typename NContainer::TCLinkedList<NPrivate::TCObjectEntry<tf_CJSONValue>>::CIterator begin(TCJSONObject<tf_CJSONValue> &_JSONObject) 
		{
			return _JSONObject.mp_Objects.f_GetIterator();
		}
		
		template <typename tf_CJSONValue>
		NContainer::CIteratorEndSentinel end(TCJSONObject<tf_CJSONValue> &_JSONObject) 
		{
			return NContainer::CIteratorEndSentinel();
		}
		
		template <typename tf_CJSONValue>
		typename NContainer::TCLinkedList<NPrivate::TCObjectEntry<tf_CJSONValue>>::CIteratorConst begin(TCJSONObject<tf_CJSONValue> const &_JSONObject) 
		{
			return _JSONObject.mp_Objects.f_GetIterator();
		}
		
		template <typename tf_CJSONValue>
		NContainer::CIteratorEndSentinel end(TCJSONObject<tf_CJSONValue> const &_JSONObject)
		{
			return NContainer::CIteratorEndSentinel();
		}
		
		template <typename t_CJSONObject>
		bool fg_ValidateType(t_CJSONObject const *_pObject, EJSONType _Type);
	}
}

#include "Malterlib_Encoding_JSON_Internal.h"

namespace NMib
{
	namespace NEncoding
	{
		template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
		using TCJSON = t_TCValue<NPrivate::TCJSONValueBase<t_TCValue, t_CTypes>>;

		using CJSON = TCJSON<TCJSONValue, NPrivate::CJSONExtraTypes>;
	}
}

#include "Malterlib_Encoding_JSON_Uninstantiated.hpp"

#define DMibEncodingJSONExternTemplate

#ifdef DMibEncodingJSONExternTemplate
#	include "Malterlib_Encoding_JSON_Instantiated.hpp"
#else
#	include "Malterlib_Encoding_JSON.hpp"
#endif

#ifndef DMibPNoShortCuts
using namespace NMib::NEncoding;
#endif
