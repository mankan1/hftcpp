
#line 1 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
/*
 * This file is open source software, licensed to you under the terms
 * of the Apache License, Version 2.0 (the "License").  See the NOTICE file
 * distributed with this work for additional information regarding copyright
 * ownership.  You may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
/*
 * Copyright (C) 2020 Cloudius Systems, Ltd.
 */

#pragma once

#include <seastar/core/ragel.hh>
#include <seastar/core/sstring.hh>
#include <unordered_map>

namespace seastar {


#line 31 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"


#line 81 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"


class http_chunk_size_and_ext_parser : public ragel_parser_base<http_chunk_size_and_ext_parser> {
    
#line 42 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
static const int start = 1;
static const int error = 0;

static const int en_main = 1;


#line 85 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
public:
    enum class state {
        error,
        eof,
        done,
    };
    std::unordered_map<sstring, sstring> _extensions;
    sstring _name;
    sstring _value;
    sstring _size;
    state _state;
public:
    void init() {
        init_base();
        _extensions = std::unordered_map<sstring, sstring>();
        _value = "";
        _size = "";
        _state = state::eof;
        
#line 69 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	{
	 _fsm_cs = start;
	}

#line 104 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
    }
    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        [[maybe_unused]] auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        bool done = false;
        if (p != pe) {
            _state = state::error;
        }
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmisleading-indentation"
#endif
        
#line 88 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  _fsm_cs )
	{
case 1:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr0;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr0;
	} else
		goto tr0;
	goto st0;
st0:
 _fsm_cs = 0;
	goto _out;
tr0:
#line 36 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 117 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 13: goto tr2;
		case 59: goto tr4;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st2;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st2;
	} else
		goto st2;
	goto st0;
tr2:
#line 48 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _size = str();
}
	goto st3;
tr7:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _name = str();
}
#line 52 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _extensions[_name] = std::move(_value);
}
	goto st3;
tr13:
#line 44 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
}
#line 52 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _extensions[_name] = std::move(_value);
}
	goto st3;
tr22:
#line 52 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _extensions[_name] = std::move(_value);
}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 167 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	if ( (*p) == 10 )
		goto tr5;
	goto st0;
tr5:
#line 56 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    done = true;
    {p++;  _fsm_cs = 12; goto _out;}
}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 182 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	goto st0;
tr4:
#line 48 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _size = str();
}
	goto st4;
tr9:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _name = str();
}
#line 52 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _extensions[_name] = std::move(_value);
}
	goto st4;
tr15:
#line 44 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
}
#line 52 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _extensions[_name] = std::move(_value);
}
	goto st4;
tr23:
#line 52 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _extensions[_name] = std::move(_value);
}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 220 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 33: goto tr6;
		case 124: goto tr6;
		case 126: goto tr6;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr6;
		} else if ( (*p) >= 35 )
			goto tr6;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr6;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr6;
		} else
			goto tr6;
	} else
		goto tr6;
	goto st0;
tr6:
#line 36 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 254 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 13: goto tr7;
		case 33: goto st5;
		case 59: goto tr9;
		case 61: goto tr10;
		case 124: goto st5;
		case 126: goto st5;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st5;
		} else if ( (*p) >= 35 )
			goto st5;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st5;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st5;
		} else
			goto st5;
	} else
		goto st5;
	goto st0;
tr10:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _name = str();
}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 291 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 34: goto st8;
		case 124: goto tr11;
		case 126: goto tr11;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr11;
		} else if ( (*p) >= 33 )
			goto tr11;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr11;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr11;
		} else
			goto tr11;
	} else
		goto tr11;
	goto st0;
tr11:
#line 36 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 325 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 13: goto tr13;
		case 33: goto st7;
		case 59: goto tr15;
		case 124: goto st7;
		case 126: goto st7;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st7;
		} else if ( (*p) >= 35 )
			goto st7;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st7;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st7;
		} else
			goto st7;
	} else
		goto st7;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 34: goto tr17;
		case 92: goto tr18;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr16;
tr16:
#line 36 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 373 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 34: goto tr20;
		case 92: goto tr21;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st9;
tr17:
#line 36 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
#line 44 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
}
	goto st10;
tr20:
#line 44 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 402 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 13: goto tr22;
		case 59: goto tr23;
	}
	goto st0;
tr18:
#line 36 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
#line 71 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{ g.mark_end(p); }
	goto st11;
tr21:
#line 71 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{ g.mark_end(p); }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 424 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	if ( (*p) == 127 )
		goto st0;
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr16;
	}
	_test_eof2:  _fsm_cs = 2; goto _test_eof; 
	_test_eof3:  _fsm_cs = 3; goto _test_eof; 
	_test_eof12:  _fsm_cs = 12; goto _test_eof; 
	_test_eof4:  _fsm_cs = 4; goto _test_eof; 
	_test_eof5:  _fsm_cs = 5; goto _test_eof; 
	_test_eof6:  _fsm_cs = 6; goto _test_eof; 
	_test_eof7:  _fsm_cs = 7; goto _test_eof; 
	_test_eof8:  _fsm_cs = 8; goto _test_eof; 
	_test_eof9:  _fsm_cs = 9; goto _test_eof; 
	_test_eof10:  _fsm_cs = 10; goto _test_eof; 
	_test_eof11:  _fsm_cs = 11; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 117 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
#ifdef __clang__
#pragma clang diagnostic pop
#endif
        if (!done) {
            if (p == eof) {
                _state = state::eof;
            } else if (p != pe) {
                _state = state::error;
            } else {
                p = nullptr;
            }
        } else {
            _state = state::done;
        }
        return p;
    }
    auto get_parsed_extensions() {
        return std::move(_extensions);
    }
    auto get_size() {
        return std::move(_size);
    }
    bool eof() const {
        return _state == state::eof;
    }
    bool failed() const {
        return _state == state::error;
    }
};


#line 148 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
// the headers in the chunk trailer are parsed the same way as in the request_parser.rl

#line 206 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"


class http_chunk_trailer_parser : public ragel_parser_base<http_chunk_trailer_parser> {
    
#line 487 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
static const int start = 1;
static const int error = 0;

static const int en_main = 1;


#line 210 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
public:
    enum class state {
        error,
        eof,
        done,
    };
    std::unordered_map<sstring, sstring> _headers;
    sstring _field_name;
    sstring _value;
    state _state;
public:
    void init() {
        init_base();
        _headers = std::unordered_map<sstring, sstring>();
        _field_name = "";
        _value = "";
        _state = state::eof;
        
#line 513 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	{
	 _fsm_cs = start;
	}

#line 228 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
    }
    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        [[maybe_unused]] auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        bool done = false;
        if (p != pe) {
            _state = state::error;
        }
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmisleading-indentation"
#endif
        
#line 532 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  _fsm_cs )
	{
case 1:
	switch( (*p) ) {
		case 13: goto st2;
		case 33: goto tr2;
		case 124: goto tr2;
		case 126: goto tr2;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr2;
		} else if ( (*p) >= 35 )
			goto tr2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr2;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr2;
		} else
			goto tr2;
	} else
		goto tr2;
	goto st0;
st0:
 _fsm_cs = 0;
	goto _out;
tr13:
#line 167 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    if (_headers.count(_field_name)) {
        _headers[_field_name] += sstring(",") + std::move(_value);
    } else {
        _headers[_field_name] = std::move(_value);
    }
}
	goto st2;
tr22:
#line 175 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 586 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	if ( (*p) == 10 )
		goto tr3;
	goto st0;
tr3:
#line 179 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    done = true;
    {p++;  _fsm_cs = 12; goto _out;}
}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 601 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	goto st0;
tr2:
#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st3;
tr14:
#line 167 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    if (_headers.count(_field_name)) {
        _headers[_field_name] += sstring(",") + std::move(_value);
    } else {
        _headers[_field_name] = std::move(_value);
    }
}
#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st3;
tr23:
#line 175 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _headers[_field_name] += sstring(" ") + std::move(_value);
}
#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 637 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 33: goto st3;
		case 58: goto tr5;
		case 124: goto st3;
		case 126: goto st3;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st3;
		} else if ( (*p) >= 35 )
			goto st3;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st3;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st3;
		} else
			goto st3;
	} else
		goto st3;
	goto st0;
tr5:
#line 157 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _field_name = str();
}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 672 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 9: goto st4;
		case 13: goto tr8;
		case 32: goto st4;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr6;
tr6:
#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 692 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 13: goto tr10;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st5;
tr8:
#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
#line 161 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st6;
tr10:
#line 161 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 727 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	if ( (*p) == 10 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 9: goto tr12;
		case 13: goto tr13;
		case 32: goto tr12;
		case 33: goto tr14;
		case 124: goto tr14;
		case 126: goto tr14;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr14;
		} else if ( (*p) >= 35 )
			goto tr14;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr14;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr14;
		} else
			goto tr14;
	} else
		goto tr14;
	goto st0;
tr12:
#line 167 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    if (_headers.count(_field_name)) {
        _headers[_field_name] += sstring(",") + std::move(_value);
    } else {
        _headers[_field_name] = std::move(_value);
    }
}
	goto st8;
tr21:
#line 175 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 781 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 9: goto st8;
		case 13: goto tr17;
		case 32: goto st8;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr15;
tr15:
#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 801 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	switch( (*p) ) {
		case 13: goto tr19;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st9;
tr17:
#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    g.mark_start(p);
}
#line 161 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st10;
tr19:
#line 161 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 836 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/chunk_parsers.hh"
	if ( (*p) == 10 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 9: goto tr21;
		case 13: goto tr22;
		case 32: goto tr21;
		case 33: goto tr23;
		case 124: goto tr23;
		case 126: goto tr23;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr23;
		} else if ( (*p) >= 35 )
			goto tr23;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr23;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr23;
		} else
			goto tr23;
	} else
		goto tr23;
	goto st0;
	}
	_test_eof2:  _fsm_cs = 2; goto _test_eof; 
	_test_eof12:  _fsm_cs = 12; goto _test_eof; 
	_test_eof3:  _fsm_cs = 3; goto _test_eof; 
	_test_eof4:  _fsm_cs = 4; goto _test_eof; 
	_test_eof5:  _fsm_cs = 5; goto _test_eof; 
	_test_eof6:  _fsm_cs = 6; goto _test_eof; 
	_test_eof7:  _fsm_cs = 7; goto _test_eof; 
	_test_eof8:  _fsm_cs = 8; goto _test_eof; 
	_test_eof9:  _fsm_cs = 9; goto _test_eof; 
	_test_eof10:  _fsm_cs = 10; goto _test_eof; 
	_test_eof11:  _fsm_cs = 11; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 241 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/chunk_parsers.rl"
#ifdef __clang__
#pragma clang diagnostic pop
#endif
        if (!done) {
            if (p == eof) {
                _state = state::eof;
            } else if (p != pe) {
                _state = state::error;
            } else {
                p = nullptr;
            }
        } else {
            _state = state::done;
        }
        return p;
    }
    auto get_parsed_headers() {
        return std::move(_headers);
    }
    bool eof() const {
        return _state == state::eof;
    }
    bool failed() const {
        return _state == state::error;
    }
};

}
