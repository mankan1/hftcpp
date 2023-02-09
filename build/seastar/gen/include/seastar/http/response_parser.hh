
#line 1 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
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
 * Copyright (C) 2015 Cloudius Systems, Ltd.
 */

#include <seastar/core/ragel.hh>
#include <memory>
#include <unordered_map>

namespace seastar {

struct http_response {
    sstring _version;
    std::unordered_map<sstring, sstring> _headers;
    int _status_code;
};


#line 35 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"


#line 120 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"


class http_response_parser : public ragel_parser_base<http_response_parser> {
    
#line 46 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
static const int start = 1;
static const int error = 0;

static const int en_main = 1;


#line 124 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
public:
    enum class state {
        error,
        eof,
        done,
    };
    std::unique_ptr<http_response> _rsp;
    sstring _field_name;
    sstring _value;
    state _state;
public:
    void init() {
        init_base();
        _rsp.reset(new http_response());
        _state = state::eof;
        
#line 70 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	{
	 _fsm_cs = start;
	}

#line 140 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
    }
    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        bool done = false;
        if (p != pe) {
            _state = state::error;
        }
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmisleading-indentation"
#endif
        
#line 89 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  _fsm_cs )
	{
case 1:
	if ( (*p) == 72 )
		goto st2;
	goto st0;
st0:
 _fsm_cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 84 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 84 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 80 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 47 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr6;
	goto st0;
tr6:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 147 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	if ( (*p) == 46 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 32 )
		goto tr9;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr9;
	goto st0;
tr9:
#line 44 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    _rsp->_version = str();
}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 177 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr10;
	goto st0;
tr10:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 191 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 32 )
		goto tr13;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr13;
	goto st0;
tr13:
#line 81 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    _rsp->_status_code = std::atoi(str().c_str());
}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 221 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	switch( (*p) ) {
		case 10: goto st0;
		case 13: goto st15;
	}
	goto st14;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 10 )
		goto st16;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 13: goto st17;
		case 33: goto tr18;
		case 124: goto tr18;
		case 126: goto tr18;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr18;
		} else if ( (*p) >= 35 )
			goto tr18;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr18;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr18;
		} else
			goto tr18;
	} else
		goto tr18;
	goto st0;
tr29:
#line 62 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    auto [iter, inserted] = _rsp->_headers.try_emplace(_field_name, std::move(_value));
    if (!inserted) {
        // RFC 7230, section 3.2.2.  Field Parsing:
        // A recipient MAY combine multiple header fields with the same field name into one
        // "field-name: field-value" pair, without changing the semantics of the message,
        // by appending each subsequent field value to the combined field value in order, separated by a comma.
        iter->second += sstring(",") + std::move(_value);
    }
}
	goto st17;
tr38:
#line 73 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    // RFC 7230, section 3.2.4.  Field Order:
    // A server that receives an obs-fold in a request message that is not
    // within a message/http container MUST either reject the message [...]
    // or replace each received obs-fold with one or more SP octets [...]
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 289 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	if ( (*p) == 10 )
		goto tr19;
	goto st0;
tr19:
#line 85 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    done = true;
    {p++;  _fsm_cs = 27; goto _out;}
}
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 304 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	goto st0;
tr18:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
	goto st18;
tr30:
#line 62 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    auto [iter, inserted] = _rsp->_headers.try_emplace(_field_name, std::move(_value));
    if (!inserted) {
        // RFC 7230, section 3.2.2.  Field Parsing:
        // A recipient MAY combine multiple header fields with the same field name into one
        // "field-name: field-value" pair, without changing the semantics of the message,
        // by appending each subsequent field value to the combined field value in order, separated by a comma.
        iter->second += sstring(",") + std::move(_value);
    }
}
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
	goto st18;
tr39:
#line 73 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    // RFC 7230, section 3.2.4.  Field Order:
    // A server that receives an obs-fold in a request message that is not
    // within a message/http container MUST either reject the message [...]
    // or replace each received obs-fold with one or more SP octets [...]
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 347 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	switch( (*p) ) {
		case 33: goto st18;
		case 58: goto tr21;
		case 124: goto st18;
		case 126: goto st18;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st18;
		} else if ( (*p) >= 35 )
			goto st18;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st18;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st18;
		} else
			goto st18;
	} else
		goto st18;
	goto st0;
tr21:
#line 48 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    _field_name = str();
}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 382 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	switch( (*p) ) {
		case 9: goto st19;
		case 13: goto tr24;
		case 32: goto st19;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr22;
tr22:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 402 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	switch( (*p) ) {
		case 13: goto tr26;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st20;
tr24:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
#line 56 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st21;
tr26:
#line 56 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 437 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	if ( (*p) == 10 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 9: goto tr28;
		case 13: goto tr29;
		case 32: goto tr28;
		case 33: goto tr30;
		case 124: goto tr30;
		case 126: goto tr30;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr30;
		} else if ( (*p) >= 35 )
			goto tr30;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr30;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr30;
		} else
			goto tr30;
	} else
		goto tr30;
	goto st0;
tr28:
#line 62 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    auto [iter, inserted] = _rsp->_headers.try_emplace(_field_name, std::move(_value));
    if (!inserted) {
        // RFC 7230, section 3.2.2.  Field Parsing:
        // A recipient MAY combine multiple header fields with the same field name into one
        // "field-name: field-value" pair, without changing the semantics of the message,
        // by appending each subsequent field value to the combined field value in order, separated by a comma.
        iter->second += sstring(",") + std::move(_value);
    }
}
	goto st23;
tr37:
#line 73 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    // RFC 7230, section 3.2.4.  Field Order:
    // A server that receives an obs-fold in a request message that is not
    // within a message/http container MUST either reject the message [...]
    // or replace each received obs-fold with one or more SP octets [...]
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 498 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	switch( (*p) ) {
		case 9: goto st23;
		case 13: goto tr33;
		case 32: goto st23;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr31;
tr31:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 518 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	switch( (*p) ) {
		case 13: goto tr35;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st24;
tr33:
#line 40 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    g.mark_start(p);
}
#line 56 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st25;
tr35:
#line 56 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
	{
    _value = str();
    trim_trailing_spaces_and_tabs(_value);
    g.mark_start(nullptr);
}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 553 "/home/mkandlikar/src/seastar-learning.git/build/seastar/gen/include/seastar/http/response_parser.hh"
	if ( (*p) == 10 )
		goto st26;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 9: goto tr37;
		case 13: goto tr38;
		case 32: goto tr37;
		case 33: goto tr39;
		case 124: goto tr39;
		case 126: goto tr39;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr39;
		} else if ( (*p) >= 35 )
			goto tr39;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr39;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr39;
		} else
			goto tr39;
	} else
		goto tr39;
	goto st0;
	}
	_test_eof2:  _fsm_cs = 2; goto _test_eof; 
	_test_eof3:  _fsm_cs = 3; goto _test_eof; 
	_test_eof4:  _fsm_cs = 4; goto _test_eof; 
	_test_eof5:  _fsm_cs = 5; goto _test_eof; 
	_test_eof6:  _fsm_cs = 6; goto _test_eof; 
	_test_eof7:  _fsm_cs = 7; goto _test_eof; 
	_test_eof8:  _fsm_cs = 8; goto _test_eof; 
	_test_eof9:  _fsm_cs = 9; goto _test_eof; 
	_test_eof10:  _fsm_cs = 10; goto _test_eof; 
	_test_eof11:  _fsm_cs = 11; goto _test_eof; 
	_test_eof12:  _fsm_cs = 12; goto _test_eof; 
	_test_eof13:  _fsm_cs = 13; goto _test_eof; 
	_test_eof14:  _fsm_cs = 14; goto _test_eof; 
	_test_eof15:  _fsm_cs = 15; goto _test_eof; 
	_test_eof16:  _fsm_cs = 16; goto _test_eof; 
	_test_eof17:  _fsm_cs = 17; goto _test_eof; 
	_test_eof27:  _fsm_cs = 27; goto _test_eof; 
	_test_eof18:  _fsm_cs = 18; goto _test_eof; 
	_test_eof19:  _fsm_cs = 19; goto _test_eof; 
	_test_eof20:  _fsm_cs = 20; goto _test_eof; 
	_test_eof21:  _fsm_cs = 21; goto _test_eof; 
	_test_eof22:  _fsm_cs = 22; goto _test_eof; 
	_test_eof23:  _fsm_cs = 23; goto _test_eof; 
	_test_eof24:  _fsm_cs = 24; goto _test_eof; 
	_test_eof25:  _fsm_cs = 25; goto _test_eof; 
	_test_eof26:  _fsm_cs = 26; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 153 "/home/mkandlikar/src/seastar-learning.git/seastar/src/http/response_parser.rl"
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
    auto get_parsed_response() {
        return std::move(_rsp);
    }
    bool eof() const {
        return _state == state::eof;
    }
    bool failed() const {
        return _state == state::error;
    }
};

}
