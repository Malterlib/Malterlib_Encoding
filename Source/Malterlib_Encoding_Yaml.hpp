// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Yaml.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"
#include "Malterlib_Encoding_EJson.h"
#include <Mib/Encoding/Base64>

#include "Malterlib_Encoding_Yaml_Common.hpp"
#include "Malterlib_Encoding_Yaml_ParseScalar.hpp"
#include "Malterlib_Encoding_Yaml_ParseBlock.hpp"
#include "Malterlib_Encoding_Yaml_ParseFlow.hpp"
#include "Malterlib_Encoding_Yaml_GenerateFlow.hpp"
#include "Malterlib_Encoding_Yaml_GenerateBlock.hpp"
#include "Malterlib_Encoding_Yaml_Timestamp.hpp"
#include "Malterlib_Encoding_Yaml_View.hpp"

namespace NMib::NEncoding
{
	template <typename t_CParent>
	template <typename t_CParseContext>
	auto TCJsonValue<t_CParent>::fs_FromStringYaml(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags) -> CValue
	{
		using CMetadataString = TCConditional<CValue::mc_bPreserveYamlMetadata && t_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		static_assert
			(
				!t_CParseContext::mc_bRecordYamlMetadata || CValue::mc_bPreserveYamlMetadata
				, "recording YAML metadata requires a YAML-metadata-preserving alias (e.g. CJsonOrderedYaml)"
			)
		;

		NYaml::fg_AssertExclusiveRecording<t_CParseContext>();

		CValue Output;
		NStr::CStr ToParse = _String;
		uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

		t_CParseContext Context;
		Context.m_pStartParse = pParse;
		Context.m_FileName = _FileName;
		Context.m_Flags = _Flags;

		CMetadataString LeadingComment;
		NYaml::fg_ParseYamlWhiteSpaceAndComments(pParse, Context, LeadingComment);
		NYaml::fg_EnsureYamlTagHandles(Context);
		NYaml::fg_ParseYamlDirectives(pParse, Context, LeadingComment);

		if (pParse[0] == '-' && pParse[1] == '-' && pParse[2] == '-' && NYaml::fg_IsYamlSeparation(pParse[3]))
		{
			pParse += 3;
			NYaml::fg_ParseYamlWhiteSpaceAndComments(pParse, Context, LeadingComment);
		}

		NYaml::TCYamlAnchors<CValue> Anchors;
		NYaml::fg_ParseYamlNode(Output, pParse, Context, Anchors);
		CMetadataString RootLineComment;
		if (!NYaml::fg_AtYamlLineStart(pParse, Context.m_pStartParse))
			NYaml::fg_ConsumeYamlLineEnd(pParse, Context, RootLineComment);
		CMetadataString TrailingComment;
		NYaml::fg_ParseYamlWhiteSpaceAndComments(pParse, Context, TrailingComment);

		if constexpr (CValue::mc_bPreserveYamlMetadata && t_CParseContext::mc_bRecordYamlMetadata)
		{
			if (!LeadingComment.f_IsEmpty())
				Output.f_Yaml().f_SetLeadingComment(fg_Move(LeadingComment));

			if (!RootLineComment.f_IsEmpty())
				Output.f_Yaml().f_SetLineComment(fg_Move(RootLineComment));

			if (!TrailingComment.f_IsEmpty())
				Output.f_Yaml().f_SetTrailingComment(fg_Move(TrailingComment));

			Output.f_Yaml().f_SetDocumentTagHandles(fg_Move(Context.m_DocumentTagHandles));
		}

		if (pParse[0] == '-' && pParse[1] == '-' && pParse[2] == '-' && NYaml::fg_IsYamlSeparation(pParse[3]))
			NYaml::fg_ThrowYamlParseError(Context, "multi-document streams not supported", pParse);

		if (pParse[0] == '.' && pParse[1] == '.' && pParse[2] == '.' && NYaml::fg_IsYamlSeparation(pParse[3]))
		{
			pParse += 3;
			NYaml::fg_ParseYamlWhiteSpaceAndComments(pParse, Context);
			if (pParse[0] == '-' && pParse[1] == '-' && pParse[2] == '-' && NYaml::fg_IsYamlSeparation(pParse[3]))
				NYaml::fg_ThrowYamlParseError(Context, "multi-document streams not supported", pParse);
		}

		if (*pParse)
			NYaml::fg_ThrowYamlParseError(Context, "Unexpected character after YAML document", pParse);

		return fg_Move(Output);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::fs_FromStringYaml(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags) -> CValue
	{
		if constexpr (CValue::mc_bPreserveYamlMetadata)
			return fs_FromStringYaml<NYaml::CRecordingParseContext>(_String, _FileName, _Flags);
		else
			return fs_FromStringYaml<NYaml::CParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::fs_FromStringYamlBlock(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags) -> CValue
	{
		if constexpr (CValue::mc_bPreserveYamlMetadata)
			return fs_FromStringYaml<NYaml::CBlockOnlyRecordingParseContext>(_String, _FileName, _Flags);
		else
			return fs_FromStringYaml<NYaml::CBlockOnlyParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::fs_FromStringYamlFlow(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags) -> CValue
	{
		if constexpr (CValue::mc_bPreserveYamlMetadata)
			return fs_FromStringYaml<NYaml::CFlowOnlyRecordingParseContext>(_String, _FileName, _Flags);
		else
			return fs_FromStringYaml<NYaml::CFlowOnlyParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	template <typename t_CParseContext>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringYamlContext(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		NStr::CStr Return;
		NStr::CStr::CAppender Appender(Return);
		NYaml::TCYamlGenerationState<CValue> GenerationState;

		if constexpr (CValue::mc_bPreserveYamlMetadata)
		{
			NYaml::fg_PrepassYamlGenerationValue(GenerationState, static_cast<CValue const &>(*this));
			GenerationState.m_pDocumentTagHandles = &this->f_Yaml().f_DocumentTagHandles();
			GenerationState.m_Position = 0;
		}

		if constexpr (CValue::mc_bPreserveYamlMetadata)
		{
			bool bEmittedDirective = false;

			for (auto const &Handle : this->f_Yaml().f_DocumentTagHandles().f_Entries())
			{
				Appender += "%TAG ";
				Appender += Handle.f_Key();
				Appender += ' ';
				Appender += Handle.f_Value();
				Appender += '\n';
				bEmittedDirective = true;
			}

			if (bEmittedDirective)
				Appender += "---\n";
		}

		bool bUseFlowStyle = _pPrettySeparator == nullptr;
		if constexpr (CValue::mc_bPreserveYamlMetadata && t_CParseContext::mc_bAllowFlowStyle)
		{
			if (this->f_Yaml().f_NodeStyle() == EYamlNodeStyle_Flow)
				bUseFlowStyle = true;
			else if (this->f_Yaml().f_NodeStyle() == EYamlNodeStyle_Block)
				bUseFlowStyle = false;
		}

		if constexpr (t_CParseContext::mc_bAllowBlockStyle)
		{
			if constexpr (t_CParseContext::mc_bCustomGenerate)
			{
				if
				(
					t_CParseContext::template fs_GenerateValue<t_CParseContext>
					(
						Appender
						, static_cast<CValue const &>(*this)
						, 0
						, bUseFlowStyle ? nullptr : (_pPrettySeparator ? _pPrettySeparator : "  ")
						, _Flags
					)
				)
				{
					return Return;
				}
			}

			if constexpr (CValue::mc_bPreserveYamlMetadata || requires (CValue const &Value) { Value.f_EType(); })
			{
				if (bUseFlowStyle)
					NYaml::fg_GenerateYamlNode(Appender, static_cast<CValue const &>(*this), _Flags, &GenerationState);
				else
					NYaml::fg_GenerateYamlBlockNode(Appender, static_cast<CValue const &>(*this), 0, _pPrettySeparator ? _pPrettySeparator : "  ", _Flags, &GenerationState);
			}
			else
			{
				if (bUseFlowStyle)
					NYaml::fg_GenerateYamlNode(Appender, static_cast<CValue const &>(*this), _Flags, static_cast<NYaml::TCYamlGenerationState<CValue> *>(nullptr));
				else
					NYaml::fg_GenerateYamlBlockNode(Appender, static_cast<CValue const &>(*this), 0, _pPrettySeparator ? _pPrettySeparator : "  ", _Flags, static_cast<NYaml::TCYamlGenerationState<CValue> *>(nullptr));
			}
		}
		else
		{
			if constexpr (t_CParseContext::mc_bCustomGenerate)
			{
				if (t_CParseContext::template fs_GenerateValue<t_CParseContext>(Appender, static_cast<CValue const &>(*this), 0, nullptr, _Flags))
					return Return;
			}

			if constexpr (CValue::mc_bPreserveYamlMetadata || requires (CValue const &Value) { Value.f_EType(); })
				NYaml::fg_GenerateYamlNode(Appender, static_cast<CValue const &>(*this), _Flags, &GenerationState);
			else
				NYaml::fg_GenerateYamlNode(Appender, static_cast<CValue const &>(*this), _Flags, static_cast<NYaml::TCYamlGenerationState<CValue> *>(nullptr));
		}

		return Return;
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringYaml(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToStringYamlContext<NYaml::CParseContext>(_pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringYamlFlow(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToStringYamlContext<NYaml::CFlowOnlyParseContext>(_pPrettySeparator, _Flags);
	}
}
