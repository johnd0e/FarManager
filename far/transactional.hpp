﻿#ifndef TRANSACTIONAL_HPP_94BF5BB0_AC7B_4D4F_AEE1_BA3BE0C1BE29
#define TRANSACTIONAL_HPP_94BF5BB0_AC7B_4D4F_AEE1_BA3BE0C1BE29
#pragma once

/*
transactional.hpp
*/
/*
Copyright © 2015 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Internal:

// Platform:

// Common:
#include "common/preprocessor.hpp"

// External:

//----------------------------------------------------------------------------

class transactional
{
public:
	virtual ~transactional() = default;

	virtual void BeginTransaction() = 0;
	virtual void EndTransaction() = 0;

	[[nodiscard]]
	auto ScopedTransaction()
	{
		class scoped_transaction
		{
		public:
			NONCOPYABLE(scoped_transaction);

			explicit scoped_transaction(transactional* const Object):
				m_Object(Object)
			{
				m_Object->BeginTransaction();
			}

			// Not make_raii_wrapper - it's implemented in terms of unique_ptr which has noexcept dtor,
			// and we must be able to throw here
			~scoped_transaction() noexcept(false)
			{
				m_Object->EndTransaction();
			}

		private:
			transactional* const m_Object;
		};

		return scoped_transaction(this);
	}
};


#endif // TRANSACTIONAL_HPP_94BF5BB0_AC7B_4D4F_AEE1_BA3BE0C1BE29
