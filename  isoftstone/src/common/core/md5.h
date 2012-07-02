// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef __SLICE_MD5_H
#define __SLICE_MD5_H

#include "escore.h"

extern "C"
{
struct md5_state_s;
}

namespace Slice
{

class LIBCORE_EXPORT MD5
{
public:

    MD5();
    MD5(const unsigned char*, int);
    ~MD5();

    void update(const unsigned char*, int);
    void finish();

    void getDigest(unsigned char*) const;

private:

    md5_state_s* _state;
    unsigned char _digest[16];
};

}

#endif
