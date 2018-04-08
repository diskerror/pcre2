
#include "Match.h"

using namespace Pcre2;

////////////////////////////////////////////////////////////////////////////////////////////////////
void Match::__construct(Php::Parameters& p)
{
	const char* expression = (const char *) p[0];
	
	uint32_t syntaxOption = ( p.size() > 1 ) ? (int32_t) p[1] : 0;
	
	this->init(expression, syntaxOption);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Php::Value Match::exec(Php::Parameters& p) const
{
	const char* subject = (const char *) p[0];
// 	Php::Value* matches = (Php::Value*) &p[1];

	//	do match
	int32_t matchCount = pcre2_match(
		this->_regex,
		(const PCRE2_UCHAR*) subject,
		PCRE2_ZERO_TERMINATED,
		(( p.size() > 2 && (int32_t) p[2] > 0) ? (int32_t) p[2] : 0),	//	offset,
		0,	//	options
		this->_match_data,
		NULL
	);
	
	if ( matchCount < PCRE2_ERROR_NOMATCH ) {
		throw Exception( matchCount );
	}
	
	if ( matchCount == PCRE2_ERROR_NOMATCH ) {
		return false;
	}

//	std::vector<std::string> matches;
	//	Match first.
//	if ( 1 ) {
		PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(this->_match_data);
		PCRE2_SIZE i;
		for (i = 0; i < (PCRE2_SIZE) matchCount; i++) {
			//	p[1] is an array set by signature in main
//			matches.emplace_back( (const char*)(subject + ovector[2*i]), (size_t)(ovector[2*i+1] - ovector[2*i]) );
			p[1][i] = (const char*)(subject + ovector[2*i]), (size_t)(ovector[2*i+1] - ovector[2*i]);
		}
//		p[1] = matches;
//	}
	//	Match all.
// 	else {
// 	}
	
	return true;
}
