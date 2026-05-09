// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
	namespace NPrivate
	{
		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(TCJsonValueBase const &_Value)
			: mp_Value(_Value.mp_Value)
			, mp_ValueTrivia(_Value.mp_ValueTrivia)
			, mp_ValueYamlMetadata(_Value.mp_ValueYamlMetadata)
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(TCJsonValueBase &_Value)
			: mp_Value(_Value.mp_Value)
			, mp_ValueTrivia(_Value.mp_ValueTrivia)
			, mp_ValueYamlMetadata(_Value.mp_ValueYamlMetadata)
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(TCJsonValueBase &&_Value)
			: mp_Value(fg_Move(_Value.mp_Value))
			, mp_ValueTrivia(fg_Move(_Value.mp_ValueTrivia))
			, mp_ValueYamlMetadata(fg_Move(_Value.mp_ValueYamlMetadata))
		{
			_Value.mp_Value.template f_Set<EJsonType_Invalid>();
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, EJsonContainerFlag tf_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_ContainerFlags> const &_Value)
		{
			_Value.mp_Value.f_Visit
				(
					[&](auto &&_Value)
					{
						if constexpr (NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>, CVoidTag>)
							mp_Value.template f_Set<EJsonType_Invalid>();
						else if constexpr (NContainer::NPrivate::TCIsVector<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>>::mc_bValue)
						{
							auto &OutArray = mp_Value.template f_Set<EJsonType_Array>();
							for (auto &Value : _Value)
								OutArray.f_Insert(CValue(Value));
						}
						else
							mp_Value = _Value;
					}
				)
			;

			constexpr bool c_bOtherPreservesComments = TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveComments;
			if constexpr (mc_bPreserveComments && c_bOtherPreservesComments)
				mp_ValueTrivia = _Value.mp_ValueTrivia;

			constexpr bool c_bOtherPreservesYamlMetadata = TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveYamlMetadata;
			if constexpr (mc_bPreserveYamlMetadata && c_bOtherPreservesYamlMetadata)
				mp_ValueYamlMetadata = _Value.mp_ValueYamlMetadata;
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, EJsonContainerFlag tf_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_ContainerFlags> &_Value)
		{
			_Value.mp_Value.f_Visit
				(
					[&](auto &&_Value)
					{
						if constexpr (NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>, CVoidTag>)
							mp_Value.template f_Set<EJsonType_Invalid>();
						else if constexpr (NContainer::NPrivate::TCIsVector<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>>::mc_bValue)
						{
							auto &OutArray = mp_Value.template f_Set<EJsonType_Array>();
							for (auto &Value : _Value)
								OutArray.f_Insert(CValue(Value));
						}
						else
							mp_Value = _Value;
					}
				)
			;

			constexpr bool c_bOtherPreservesComments = TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveComments;
			if constexpr (mc_bPreserveComments && c_bOtherPreservesComments)
				mp_ValueTrivia = _Value.mp_ValueTrivia;

			constexpr bool c_bOtherPreservesYamlMetadata = TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveYamlMetadata;
			if constexpr (mc_bPreserveYamlMetadata && c_bOtherPreservesYamlMetadata)
				mp_ValueYamlMetadata = _Value.mp_ValueYamlMetadata;
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, EJsonContainerFlag tf_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_ContainerFlags> &&_Value)
		{
			_Value.mp_Value.f_Visit
				(
					[&](auto &&_Value)
					{
						if constexpr (NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>, CVoidTag>)
							mp_Value.template f_Set<EJsonType_Invalid>();
						else if constexpr (NContainer::NPrivate::TCIsVector<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>>::mc_bValue)
						{
							auto &OutArray = mp_Value.template f_Set<EJsonType_Array>();
							for (auto &Value : _Value)
								OutArray.f_Insert(CValue(fg_Move(Value)));
						}
						else
							mp_Value = fg_Move(_Value);
					}
				)
			;

			constexpr bool c_bOtherPreservesComments = TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveComments;
			if constexpr (mc_bPreserveComments && c_bOtherPreservesComments)
				mp_ValueTrivia = fg_Move(_Value.mp_ValueTrivia);

			constexpr bool c_bOtherPreservesYamlMetadata = TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveYamlMetadata;
			if constexpr (mc_bPreserveYamlMetadata && c_bOtherPreservesYamlMetadata)
				mp_ValueYamlMetadata = fg_Move(_Value.mp_ValueYamlMetadata);

			_Value.mp_Value.template f_Set<EJsonType_Invalid>();
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(bool _Value)
			: mp_Value(CJsonBoolean(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(pfp64 _Value)
			: mp_Value(fp64(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(pfp32 _Value)
			: mp_Value(fp64(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(fp32 _Value)
			: mp_Value(fp64(_Value))
		{
		}


		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase()
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::~TCJsonValueBase()
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonTriviaView<TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>> TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::f_Trivia()
			requires (mc_bPreserveComments)
		{
			return TCJsonTriviaView<TCJsonValueBase>(*this);
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCJsonTriviaConstView<TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>> TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::f_Trivia() const
			requires (mc_bPreserveComments)
		{
			return TCJsonTriviaConstView<TCJsonValueBase>(*this);
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCYamlView<TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>> TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::f_Yaml()
			requires (mc_bPreserveYamlMetadata)
		{
			return TCYamlView<TCJsonValueBase>(*this);
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
		TCYamlConstView<TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>> TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::f_Yaml() const
			requires (mc_bPreserveYamlMetadata)
		{
			return TCYamlConstView<TCJsonValueBase>(*this);
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		TCObjectEntry<t_CJsonValue, t_ContainerFlags>::TCObjectEntry()
		{
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		NStr::CStr const &TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_Name() const
		{
			if constexpr (mc_bOrdered)
				return this->mp_Name;
			else
				return NContainer::TCMap<NStr::CStr, TCObjectEntry>::fs_GetKey(*this);
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		NStr::CStr const &TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_Key() const
		{
			return f_Name();
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		t_CJsonValue &TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_Value()
		{
			return mp_Value;
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		t_CJsonValue const &TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_Value() const
		{
			return mp_Value;
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		TCJsonKeyTriviaView<TCObjectEntry<t_CJsonValue, t_ContainerFlags>> TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_KeyTrivia()
			requires (mc_bPreserveComments)
		{
			return TCJsonKeyTriviaView<TCObjectEntry>(*this);
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		TCJsonKeyTriviaConstView<TCObjectEntry<t_CJsonValue, t_ContainerFlags>> TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_KeyTrivia() const
			requires (mc_bPreserveComments)
		{
			return TCJsonKeyTriviaConstView<TCObjectEntry>(*this);
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		TCYamlKeyView<TCObjectEntry<t_CJsonValue, t_ContainerFlags>> TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_KeyYaml()
			requires (mc_bPreserveYamlMetadata)
		{
			return TCYamlKeyView<TCObjectEntry>(*this);
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		TCYamlKeyConstView<TCObjectEntry<t_CJsonValue, t_ContainerFlags>> TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_KeyYaml() const
			requires (mc_bPreserveYamlMetadata)
		{
			return TCYamlKeyConstView<TCObjectEntry>(*this);
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		bool TCObjectEntry<t_CJsonValue, t_ContainerFlags>::operator == (TCObjectEntry const &_Right) const noexcept
		{
			if (f_Name() != _Right.f_Name())
				return false;
			return mp_Value == _Right.mp_Value;
		}

		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		COrdering_Partial TCObjectEntry<t_CJsonValue, t_ContainerFlags>::operator <=> (TCObjectEntry const &_Right) const noexcept
		{
			if (auto Result = f_Name() <=> _Right.f_Name(); Result != 0)
				return Result;

			return mp_Value <=> _Right.mp_Value;
		}
	}
}

#include "Malterlib_Encoding_Json_Trivia.hpp"
#include "Malterlib_Encoding_Json_Value.hpp"
#include "Malterlib_Encoding_Json_Object.hpp"
