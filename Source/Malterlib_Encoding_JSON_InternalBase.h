#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		template <typename t_CJSONValue>
		class TCJSONObject;

		namespace NPrivate
		{
			class CObjectEntryBase
			{
				template <typename t_CJSONValue>
				friend class NEncoding::TCJSONObject;

			protected:
				
				NStr::CStr mp_Name;
				DMibIntrusiveLink(CObjectEntryBase, NIntrusive::TCAVLLink<>, mp_Link);

				CObjectEntryBase();
				CObjectEntryBase(CObjectEntryBase const &_Other);
				CObjectEntryBase(CObjectEntryBase &&_Other);

				class CCompare
				{
				public:
					inline_small NStr::CStr const &operator () (CObjectEntryBase const &_Node) const
					{
						return _Node.mp_Name;
					}
				};
			};

			template <typename t_CJSONValue>
			struct TCObjectEntry : public CObjectEntryBase
			{
				template <typename t_CJSONValue2>
				friend class NEncoding::TCJSONObject;

			public:
				TCObjectEntry();

				bool operator == (TCObjectEntry const &_Right) const;
				bool operator < (TCObjectEntry const &_Right) const;

				NStr::CStr const &f_Name() const;
				t_CJSONValue &f_Value();
				t_CJSONValue const &f_Value() const;

				template <typename tf_CStream>
				void f_Feed(tf_CStream &_Stream) const;
				template <typename tf_CStream>
				void f_Consume(tf_CStream &_Stream);
				
			protected:
				t_CJSONValue mp_Value;
			};

		}
	}
}

