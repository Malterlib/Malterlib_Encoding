// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/Storage/Variant>
#include <Mib/CommandLine/AnsiEncoding>

#include "Malterlib_Encoding_JSON_InternalBase.h"

#define DMibEncodingJSONExternTemplate

namespace NMib::NEncoding
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

	enum EJSONDialectFlag : uint32
	{
		EJSONDialectFlag_None = 0
		, EJSONDialectFlag_AllowUndefined = DMibBit(0)
		, EJSONDialectFlag_AllowInvalidFloat = DMibBit(1)
		, EJSONDialectFlag_HighPrecisionFloat = DMibBit(2)
		, EJSONDialectFlag_TrimWhitespace = DMibBit(3)

		, EJSONDialectFlag_All = EJSONDialectFlag_AllowUndefined | EJSONDialectFlag_AllowInvalidFloat | EJSONDialectFlag_HighPrecisionFloat | EJSONDialectFlag_TrimWhitespace
	};

	template <typename t_CJSONValue, bool t_bOrdered>
	struct TCJSONObject;

	template <typename t_CParent>
	struct TCJSONValue : public t_CParent
	{
	protected:
		using CValue = typename t_CParent::CValue;
		struct CDummy {};
	public:
		typedef TCJSONObject<CValue, t_CParent::mc_bOrdered> CObject;
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
			inline_always CKeyValue operator = (CValue const &_Value) &&;
			inline_always CKeyValue operator = (std::initializer_list<CVoidTag> const &_Initializer) &&;
		private:
			CKey(CKey const &_Other);
		};

		template <typename tf_CType>
		TCJSONValue(tf_CType &&_Type)
			requires
			(
				NTraits::cConstructibleWith<t_CParent, tf_CType &&>
				&& !NPrivate::TCIsTCJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
				&& !NPrivate::TCIsTCEJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
			)
#ifdef DCompiler_MSVC_Workaround
			: t_CParent(fg_Forward<tf_CType>(_Type))
		{
		}
#else
		;
#endif
		TCJSONValue();
		TCJSONValue(TCJSONValue const &_Other);
		TCJSONValue(TCJSONValue &&_Other);
		TCJSONValue(TCJSONValue const &&_Other);
		TCJSONValue(EJSONType _Type);
		TCJSONValue(ch8 const *_pValue);

		template <typename ...tfp_CValues>
		TCJSONValue(tfp_CValues && ...p_Values)
			requires ((NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiersType<tfp_CValues>, CKeyValue> && (sizeof...(p_Values) > 0)) && ...)
		;

		TCJSONValue(NContainer::CSecureByteVector const &_Value) = delete;
		TCJSONValue(NContainer::CSecureByteVector &_Value) = delete;
		TCJSONValue(NContainer::CSecureByteVector &&_Value) = delete;

		template <typename tf_CType>
		auto operator = (tf_CType &&_Value) -> TCEnableIfType<!NTraits::TCIsSame<decltype(this->mp_Value = fg_Forward<tf_CType>(_Value)), CDummy>::mc_Value, CValue> &
#ifdef DCompiler_MSVC_Workaround
		{
			this->mp_Value = fg_Forward<tf_CType>(_Value);
			return static_cast<CValue &>(*this);
		}
#else
		;
#endif

		CValue &operator = (NContainer::CSecureByteVector const &_Value) = delete;
		CValue &operator = (NContainer::CSecureByteVector &_Value) = delete;
		CValue &operator = (NContainer::CSecureByteVector &&_Value) = delete;

		template <typename tf_CParent>
		static TCJSONValue fs_FromCompatible(TCJSONValue<tf_CParent> const &_Other);
		template <typename tf_CParent>
		static TCJSONValue fs_FromCompatible(TCJSONValue<tf_CParent> &&_Other);
		template <typename tf_CParent>
		static TCJSONValue fs_FromCompatible(TCJSONValue<tf_CParent> const &&_Other);

		CValue &operator = (TCJSONValue const &_Value);
		CValue &operator = (TCJSONValue &&_Value);
		CValue &operator = (pfp64 _Value);
		CValue &operator = (pfp32 _Value);
		CValue &operator = (fp32 _Value);
		CValue &operator = (bool _Value);
		CValue &operator = (EJSONType _Type);
		CValue &operator = (ch8 const *_pValue);

		bool operator == (TCJSONValue const &_Right) const;
		COrdering_Partial operator <=> (TCJSONValue const &_Right) const;

		EJSONType f_Type() const;
		void f_SetType(EJSONType _Type);

		bool f_IsValid() const;
		bool f_IsNull() const;
		bool f_IsString() const;
		bool f_IsStringArray() const;
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
		CObject const &f_Object() const;
		CObject &f_Object();
		NContainer::TCVector<CValue> const &f_Array() const;
		NContainer::TCVector<CValue> &f_Array();
		NContainer::TCVector<NStr::CStr> f_StringArray() const &;
		NContainer::TCVector<NStr::CStr> f_StringArray() &&;

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
		CValue &operator () (NStr::CStr const &_Name);
		bool f_RemoveMember(NStr::CStr const &_Name);
		CValue f_GetMemberValue(NStr::CStr const &_Name, CValue const &_Default) const;
		CValue f_GetMemberValue(NStr::CStr const &_Name, CValue &&_Default) const;
		void f_SortObjectsLexicographically();

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

		static CValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = {}, bool _bConvertNullToSpace = false, EJSONDialectFlag _Flags = EJSONDialectFlag_None);
		NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t", EJSONDialectFlag _Flags = EJSONDialectFlag_None) const;
		NStr::CStr f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJSONDialectFlag _Flags = EJSONDialectFlag_None) const;

	protected:
		template <typename t_CJSONValue2, bool t_bOrdered2>
		friend struct TCJSONObject;

		template <template <typename t_CParent2> class t_TCValue2, typename t_CTypes2, bool t_bOrdered2>
		friend struct NPrivate::TCJSONValueBase;

		template <typename tf_CParent>
		explicit TCJSONValue(TCJSONValue<tf_CParent> const &_Other);
		template <typename tf_CParent>
		explicit TCJSONValue(TCJSONValue<tf_CParent> &&_Other);
		template <typename tf_CParent>
		explicit TCJSONValue(TCJSONValue<tf_CParent> const &&_Other);

		inline_always void fp_CheckType(EJSONType _Type) const;
		inline_always void fp_PromoteType(EJSONType _Type);
	};

	template <typename t_CJSONValue, bool t_bOrdered>
	struct TCJSONObject
	{
	public:
		typedef NPrivate::TCObjectEntry<t_CJSONValue, t_bOrdered> CObjectEntry;
	private:
		typedef typename NPrivate::CObjectEntryBase::CCompare CCompare;

		using CObjects = typename TCChooseType<t_bOrdered, NContainer::TCLinkedList<CObjectEntry>, NContainer::TCMap<NStr::CStr, CObjectEntry>>::CType;
		using CObjectsTree = typename TCChooseType
			<
				t_bOrdered
				, NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>
				, CEmpty
			>::CType
		;

	public:
		TCJSONObject();
		~TCJSONObject();
		TCJSONObject(TCJSONObject const &_Other);
		TCJSONObject(TCJSONObject &&_Other);

		template <typename tf_CJSONValue, bool tf_bOrdered>
		explicit TCJSONObject(TCJSONObject<tf_CJSONValue, tf_bOrdered> const &_Other);
		template <typename tf_CJSONValue, bool tf_bOrdered>
		explicit TCJSONObject(TCJSONObject<tf_CJSONValue, tf_bOrdered> &&_Other);

		bool operator == (TCJSONObject const &_Right) const;
		COrdering_Partial operator <=> (TCJSONObject const &_Right) const;

		t_CJSONValue const *f_GetMember(NStr::CStr const &_Name) const;
		t_CJSONValue *f_GetMember(NStr::CStr const &_Name);
		t_CJSONValue const *f_GetMember(NStr::CStr const &_Name, EJSONType _Type) const;
		t_CJSONValue *f_GetMember(NStr::CStr const &_Name, EJSONType _Type);
		t_CJSONValue f_GetMemberValue(NStr::CStr const &_Name, t_CJSONValue const &_Default) const;
		t_CJSONValue f_GetMemberValue(NStr::CStr const &_Name, t_CJSONValue &&_Default) const;
		t_CJSONValue &f_CreateMember(NStr::CStr const &_Name);
		t_CJSONValue &f_CreateMember(NStr::CStr &&_Name);

		t_CJSONValue &operator [] (NStr::CStr const &_Name);
		t_CJSONValue const &operator [] (NStr::CStr const &_Name) const;
		t_CJSONValue &operator () (NStr::CStr const &_Name);

		bool f_RemoveMember(NStr::CStr const &_Name);
		void f_RemoveMember(typename CObjects::CIteratorConst &_Iterator)
			requires (t_bOrdered)
		;
		void f_RemoveMember(typename CObjects::CIterator &_Iterator);
		void f_RemoveMember(typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator &_Iterator)
			requires (t_bOrdered)
		;

		typename CObjects::CIteratorConst f_OrderedIterator() const;
		typename CObjects::CIterator f_OrderedIterator();

		typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator f_SortedIterator() const
			requires (t_bOrdered)
		;

		template <typename tf_FOnObject>
		void f_ExtractAll(tf_FOnObject &&_fOnObject);

		bool f_IsEmpty() const;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
		void f_SortObjectsLexicographically();

	private:
		CObjects mp_Objects;
		DMibNoUniqueAddress CObjectsTree mp_ObjectTree;
	};

#ifndef DDocumentation_Doxygen
	template <typename tf_CJSONValue, bool tf_bOrdered>
	auto begin(TCJSONObject<tf_CJSONValue, tf_bOrdered> &_JSONObject)
	{
		return _JSONObject.f_OrderedIterator();
	}

	template <typename tf_CJSONValue, bool tf_bOrdered>
	NContainer::CIteratorEndSentinel end(TCJSONObject<tf_CJSONValue, tf_bOrdered> &_JSONObject)
	{
		return NContainer::CIteratorEndSentinel();
	}

	template <typename tf_CJSONValue, bool tf_bOrdered>
	auto begin(TCJSONObject<tf_CJSONValue, tf_bOrdered> const &_JSONObject)
	{
		return _JSONObject.f_OrderedIterator();
	}

	template <typename tf_CJSONValue, bool tf_bOrdered>
	NContainer::CIteratorEndSentinel end(TCJSONObject<tf_CJSONValue, tf_bOrdered> const &_JSONObject)
	{
		return NContainer::CIteratorEndSentinel();
	}
#endif

	template <typename t_CJSONObject>
	bool fg_ValidateType(t_CJSONObject const *_pObject, EJSONType _Type);

	NStr::CStr fg_JSONTypeToString(EJSONType _Type);
}

#include "Malterlib_Encoding_JSON_Internal.h"

namespace NMib::NEncoding
{
	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	using TCJSON = t_TCValue<NPrivate::TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>>;

	using CJSONOrdered = TCJSON<TCJSONValue, NPrivate::CJSONExtraTypes, true>;
	using CJSONSorted = TCJSON<TCJSONValue, NPrivate::CJSONExtraTypes, false>;

#ifdef DMibEncodingJSONExternTemplate
	using CJSONValueBaseOrdered = NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, true>;
	using CJSONValueJSONOrdered = TCJSONValue<CJSONValueBaseOrdered>;

	using CJSONValueBaseSorted = NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, false>;
	using CJSONValueJSONSorted = TCJSONValue<CJSONValueBaseSorted>;
#endif
}

#include "Malterlib_Encoding_JSON_Uninstantiated.hpp"

#ifdef DMibEncodingJSONExternTemplate
#	include "Malterlib_Encoding_JSON_Instantiated.hpp"
#	include "Malterlib_Encoding_JSON_InstantiatedSorted.hpp"
#else
#	include "Malterlib_Encoding_JSON.hpp"
#endif

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
