#ifndef _LCSH_VERSION_H_
#define _LCSH_VERSION_H_

static const char* CommitTime = "2010/04/12 22:44:08";
static const char* BuildTime = "2010/04/14 20:55:29";
static const char* SvnVersion = "167";
static const char* CompanyName = "Áú³ÇÊ«ºì";
static const char* LegalCopyright = "Copyright (C) 2010";
static const char* ProductName = "LSCADA";


static const char* getSvnCommitTime()
{
	return CommitTime;
}

static const char* getSvnBuildTime()
{
	return BuildTime;
}

static const char* getSvnVersion()
{
	return SvnVersion;
}

static const char* getCompanyName()
{
	return CompanyName;
}

static const char* getCopyRight()
{
	return LegalCopyright;
}

static const char* getProductName()
{
	return ProductName;
}

#endif