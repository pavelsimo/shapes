/* Generated by re2c 1.1.1 on Sat Apr 20 11:09:50 2019 */
#pragma once

#include <ciso646>
#include <iostream>

namespace simo
{

namespace shapes
{

/*!
 * @brief a Well-known text (WKT) markup language lexer
 * @ingroup wkt
 *
 * @since 0.0.1
 */
class WktLexer
{
  public:

    /*!
     * @brief creates a wkt lexer from the given source
     * @param source the source string
     *
     * @since 0.0.1
     */
    WktLexer(const char* source)
        : content(source)
    {
        start = cursor = source;
        limit          = content + strlen(source);
    }

    /*!
     * @brief scan the next token
     * @return the numeric token identifier
     *
     * @since 0.0.1
     */
    int scan()
    {

        /// pointer for backtracking information
        const char* marker = nullptr;

        start = cursor;

        
{
	char yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128,   0,   0, 128,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *cursor;
	if (yych <= 'D') {
		if (yych <= '\'') {
			if (yych <= '\f') {
				if (yych <= 0x00) goto shapes_wkt_lexer_2;
				if (yych <= 0x08) goto shapes_wkt_lexer_4;
				if (yych <= '\n') goto shapes_wkt_lexer_6;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= '\r') goto shapes_wkt_lexer_6;
				if (yych == ' ') goto shapes_wkt_lexer_6;
				goto shapes_wkt_lexer_4;
			}
		} else {
			if (yych <= ',') {
				if (yych <= '(') goto shapes_wkt_lexer_8;
				if (yych <= ')') goto shapes_wkt_lexer_10;
				if (yych <= '+') goto shapes_wkt_lexer_4;
				goto shapes_wkt_lexer_12;
			} else {
				if (yych <= '/') {
					if (yych <= '-') goto shapes_wkt_lexer_14;
					goto shapes_wkt_lexer_4;
				} else {
					if (yych <= '0') goto shapes_wkt_lexer_15;
					if (yych <= '9') goto shapes_wkt_lexer_17;
					goto shapes_wkt_lexer_4;
				}
			}
		}
	} else {
		if (yych <= 'd') {
			if (yych <= 'K') {
				if (yych <= 'E') goto shapes_wkt_lexer_19;
				if (yych == 'G') goto shapes_wkt_lexer_20;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= 'M') {
					if (yych <= 'L') goto shapes_wkt_lexer_21;
					goto shapes_wkt_lexer_22;
				} else {
					if (yych == 'P') goto shapes_wkt_lexer_23;
					goto shapes_wkt_lexer_4;
				}
			}
		} else {
			if (yych <= 'k') {
				if (yych <= 'e') goto shapes_wkt_lexer_19;
				if (yych == 'g') goto shapes_wkt_lexer_20;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= 'm') {
					if (yych <= 'l') goto shapes_wkt_lexer_21;
					goto shapes_wkt_lexer_22;
				} else {
					if (yych == 'p') goto shapes_wkt_lexer_23;
					goto shapes_wkt_lexer_4;
				}
			}
		}
	}
shapes_wkt_lexer_2:
	++cursor;
	{ return WKT_END_OF_INPUT; }
shapes_wkt_lexer_4:
	++cursor;
shapes_wkt_lexer_5:
	{ return WKT_PARSE_ERROR; }
shapes_wkt_lexer_6:
	++cursor;
	{ return scan(); }
shapes_wkt_lexer_8:
	++cursor;
	{ return WKT_LPAREN; }
shapes_wkt_lexer_10:
	++cursor;
	{ return WKT_RPAREN; }
shapes_wkt_lexer_12:
	++cursor;
	{ return WKT_COMMA; }
shapes_wkt_lexer_14:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_5;
	if (yych <= '0') goto shapes_wkt_lexer_15;
	if (yych <= '9') goto shapes_wkt_lexer_17;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_15:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= 'D') {
		if (yych == '.') goto shapes_wkt_lexer_24;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_26;
		if (yych == 'e') goto shapes_wkt_lexer_26;
	}
shapes_wkt_lexer_16:
	{ return WKT_NUM; }
shapes_wkt_lexer_17:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yybm[0+yych] & 64) {
		goto shapes_wkt_lexer_17;
	}
	if (yych <= 'D') {
		if (yych == '.') goto shapes_wkt_lexer_24;
		goto shapes_wkt_lexer_16;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_26;
		if (yych == 'e') goto shapes_wkt_lexer_26;
		goto shapes_wkt_lexer_16;
	}
shapes_wkt_lexer_19:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'M') goto shapes_wkt_lexer_27;
	if (yych == 'm') goto shapes_wkt_lexer_27;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_20:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'E') goto shapes_wkt_lexer_28;
	if (yych == 'e') goto shapes_wkt_lexer_28;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_21:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'I') goto shapes_wkt_lexer_29;
	if (yych == 'i') goto shapes_wkt_lexer_29;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_22:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'U') goto shapes_wkt_lexer_30;
	if (yych == 'u') goto shapes_wkt_lexer_30;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_23:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'O') goto shapes_wkt_lexer_31;
	if (yych == 'o') goto shapes_wkt_lexer_31;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_24:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_25;
	if (yych <= '9') goto shapes_wkt_lexer_32;
shapes_wkt_lexer_25:
	cursor = marker;
	if (yyaccept <= 4) {
		if (yyaccept <= 2) {
			if (yyaccept <= 1) {
				if (yyaccept == 0) {
					goto shapes_wkt_lexer_16;
				} else {
					goto shapes_wkt_lexer_5;
				}
			} else {
				goto shapes_wkt_lexer_55;
			}
		} else {
			if (yyaccept == 3) {
				goto shapes_wkt_lexer_75;
			} else {
				goto shapes_wkt_lexer_96;
			}
		}
	} else {
		if (yyaccept <= 6) {
			if (yyaccept == 5) {
				goto shapes_wkt_lexer_99;
			} else {
				goto shapes_wkt_lexer_123;
			}
		} else {
			if (yyaccept == 7) {
				goto shapes_wkt_lexer_138;
			} else {
				goto shapes_wkt_lexer_150;
			}
		}
	}
shapes_wkt_lexer_26:
	yych = *++cursor;
	if (yych <= ',') {
		if (yych == '+') goto shapes_wkt_lexer_34;
		goto shapes_wkt_lexer_25;
	} else {
		if (yych <= '-') goto shapes_wkt_lexer_34;
		if (yych <= '/') goto shapes_wkt_lexer_25;
		if (yych <= '9') goto shapes_wkt_lexer_35;
		goto shapes_wkt_lexer_25;
	}
shapes_wkt_lexer_27:
	yych = *++cursor;
	if (yych == 'P') goto shapes_wkt_lexer_37;
	if (yych == 'p') goto shapes_wkt_lexer_37;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_28:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_38;
	if (yych == 'o') goto shapes_wkt_lexer_38;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_29:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_39;
	if (yych == 'n') goto shapes_wkt_lexer_39;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_30:
	yych = *++cursor;
	if (yych == 'L') goto shapes_wkt_lexer_40;
	if (yych == 'l') goto shapes_wkt_lexer_40;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_31:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych == 'I') goto shapes_wkt_lexer_41;
		if (yych <= 'K') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_42;
	} else {
		if (yych <= 'i') {
			if (yych <= 'h') goto shapes_wkt_lexer_25;
			goto shapes_wkt_lexer_41;
		} else {
			if (yych == 'l') goto shapes_wkt_lexer_42;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_32:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= 'D') {
		if (yych <= '/') goto shapes_wkt_lexer_16;
		if (yych <= '9') goto shapes_wkt_lexer_32;
		goto shapes_wkt_lexer_16;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_26;
		if (yych == 'e') goto shapes_wkt_lexer_26;
		goto shapes_wkt_lexer_16;
	}
shapes_wkt_lexer_34:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_25;
	if (yych >= ':') goto shapes_wkt_lexer_25;
shapes_wkt_lexer_35:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_16;
	if (yych <= '9') goto shapes_wkt_lexer_35;
	goto shapes_wkt_lexer_16;
shapes_wkt_lexer_37:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_43;
	if (yych == 't') goto shapes_wkt_lexer_43;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_38:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_44;
	if (yych == 'm') goto shapes_wkt_lexer_44;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_39:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_45;
	if (yych == 'e') goto shapes_wkt_lexer_45;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_40:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_46;
	if (yych == 't') goto shapes_wkt_lexer_46;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_41:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_47;
	if (yych == 'n') goto shapes_wkt_lexer_47;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_42:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_48;
	if (yych == 'y') goto shapes_wkt_lexer_48;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_43:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_49;
	if (yych == 'y') goto shapes_wkt_lexer_49;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_44:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_51;
	if (yych == 'e') goto shapes_wkt_lexer_51;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_45:
	yych = *++cursor;
	if (yych == 'S') goto shapes_wkt_lexer_52;
	if (yych == 's') goto shapes_wkt_lexer_52;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_46:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_53;
	if (yych == 'i') goto shapes_wkt_lexer_53;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_47:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_54;
	if (yych == 't') goto shapes_wkt_lexer_54;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_48:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_56;
	if (yych == 'g') goto shapes_wkt_lexer_56;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_49:
	++cursor;
	{ return WKT_EMPTY_SET; }
shapes_wkt_lexer_51:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_57;
	if (yych == 't') goto shapes_wkt_lexer_57;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_52:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_58;
	if (yych == 't') goto shapes_wkt_lexer_58;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_53:
	yych = *++cursor;
	if (yych <= 'P') {
		if (yych == 'L') goto shapes_wkt_lexer_59;
		if (yych <= 'O') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_60;
	} else {
		if (yych <= 'l') {
			if (yych <= 'k') goto shapes_wkt_lexer_25;
			goto shapes_wkt_lexer_59;
		} else {
			if (yych == 'p') goto shapes_wkt_lexer_60;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_54:
	yyaccept = 2;
	yych = *(marker = ++cursor);
	if (yybm[0+yych] & 128) {
		goto shapes_wkt_lexer_61;
	}
	if (yych <= 'Z') {
		if (yych == 'M') goto shapes_wkt_lexer_63;
		if (yych >= 'Z') goto shapes_wkt_lexer_65;
	} else {
		if (yych <= 'm') {
			if (yych >= 'm') goto shapes_wkt_lexer_63;
		} else {
			if (yych == 'z') goto shapes_wkt_lexer_65;
		}
	}
shapes_wkt_lexer_55:
	{ return WKT_POINT_TAGGED_TEXT; }
shapes_wkt_lexer_56:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_67;
	if (yych == 'o') goto shapes_wkt_lexer_67;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_57:
	yych = *++cursor;
	if (yych == 'R') goto shapes_wkt_lexer_68;
	if (yych == 'r') goto shapes_wkt_lexer_68;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_58:
	yych = *++cursor;
	if (yych == 'R') goto shapes_wkt_lexer_69;
	if (yych == 'r') goto shapes_wkt_lexer_69;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_59:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_70;
	if (yych == 'i') goto shapes_wkt_lexer_70;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_60:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_71;
	if (yych == 'o') goto shapes_wkt_lexer_71;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_61:
	yych = *++cursor;
	if (yybm[0+yych] & 128) {
		goto shapes_wkt_lexer_61;
	}
	if (yych <= 'Z') {
		if (yych == 'M') goto shapes_wkt_lexer_63;
		if (yych <= 'Y') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_65;
	} else {
		if (yych <= 'm') {
			if (yych <= 'l') goto shapes_wkt_lexer_25;
		} else {
			if (yych == 'z') goto shapes_wkt_lexer_65;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_63:
	++cursor;
	{ return WKT_POINT_M_TAGGED_TEXT; }
shapes_wkt_lexer_65:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_72;
	if (yych == 'm') goto shapes_wkt_lexer_72;
	{ return WKT_POINT_Z_TAGGED_TEXT; }
shapes_wkt_lexer_67:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_74;
	if (yych == 'n') goto shapes_wkt_lexer_74;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_68:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_76;
	if (yych == 'y') goto shapes_wkt_lexer_76;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_69:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_77;
	if (yych == 'i') goto shapes_wkt_lexer_77;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_70:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_78;
	if (yych == 'n') goto shapes_wkt_lexer_78;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_71:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych == 'I') goto shapes_wkt_lexer_79;
		if (yych <= 'K') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_80;
	} else {
		if (yych <= 'i') {
			if (yych <= 'h') goto shapes_wkt_lexer_25;
			goto shapes_wkt_lexer_79;
		} else {
			if (yych == 'l') goto shapes_wkt_lexer_80;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_72:
	++cursor;
	{ return WKT_POINT_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_74:
	yyaccept = 3;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_75;
			if (yych <= '\n') goto shapes_wkt_lexer_81;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_81;
			if (yych == ' ') goto shapes_wkt_lexer_81;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_83;
			if (yych == 'Z') goto shapes_wkt_lexer_85;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_83;
			if (yych == 'z') goto shapes_wkt_lexer_85;
		}
	}
shapes_wkt_lexer_75:
	{ return WKT_POLYGON_TAGGED_TEXT; }
shapes_wkt_lexer_76:
	yych = *++cursor;
	if (yych == 'C') goto shapes_wkt_lexer_87;
	if (yych == 'c') goto shapes_wkt_lexer_87;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_77:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_88;
	if (yych == 'n') goto shapes_wkt_lexer_88;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_78:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_89;
	if (yych == 'e') goto shapes_wkt_lexer_89;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_79:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_90;
	if (yych == 'n') goto shapes_wkt_lexer_90;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_80:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_91;
	if (yych == 'y') goto shapes_wkt_lexer_91;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_81:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_81;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_81;
			if (yych == ' ') goto shapes_wkt_lexer_81;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_83;
			if (yych == 'Z') goto shapes_wkt_lexer_85;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_83;
			if (yych == 'z') goto shapes_wkt_lexer_85;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_83:
	++cursor;
	{ return WKT_POLYGON_M_TAGGED_TEXT; }
shapes_wkt_lexer_85:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_92;
	if (yych == 'm') goto shapes_wkt_lexer_92;
	{ return WKT_POLYGON_Z_TAGGED_TEXT; }
shapes_wkt_lexer_87:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_94;
	if (yych == 'o') goto shapes_wkt_lexer_94;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_88:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_95;
	if (yych == 'g') goto shapes_wkt_lexer_95;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_89:
	yych = *++cursor;
	if (yych == 'S') goto shapes_wkt_lexer_97;
	if (yych == 's') goto shapes_wkt_lexer_97;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_90:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_98;
	if (yych == 't') goto shapes_wkt_lexer_98;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_91:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_100;
	if (yych == 'g') goto shapes_wkt_lexer_100;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_92:
	++cursor;
	{ return WKT_POLYGON_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_94:
	yych = *++cursor;
	if (yych == 'L') goto shapes_wkt_lexer_101;
	if (yych == 'l') goto shapes_wkt_lexer_101;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_95:
	yyaccept = 4;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_96;
			if (yych <= '\n') goto shapes_wkt_lexer_102;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_102;
			if (yych == ' ') goto shapes_wkt_lexer_102;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_104;
			if (yych == 'Z') goto shapes_wkt_lexer_106;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_104;
			if (yych == 'z') goto shapes_wkt_lexer_106;
		}
	}
shapes_wkt_lexer_96:
	{ return WKT_LINESTRING_TAGGED_TEXT; }
shapes_wkt_lexer_97:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_108;
	if (yych == 't') goto shapes_wkt_lexer_108;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_98:
	yyaccept = 5;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_99;
			if (yych <= '\n') goto shapes_wkt_lexer_109;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_109;
			if (yych == ' ') goto shapes_wkt_lexer_109;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_111;
			if (yych == 'Z') goto shapes_wkt_lexer_113;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_111;
			if (yych == 'z') goto shapes_wkt_lexer_113;
		}
	}
shapes_wkt_lexer_99:
	{ return WKT_MULTIPOINT_TAGGED_TEXT; }
shapes_wkt_lexer_100:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_115;
	if (yych == 'o') goto shapes_wkt_lexer_115;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_101:
	yych = *++cursor;
	if (yych == 'L') goto shapes_wkt_lexer_116;
	if (yych == 'l') goto shapes_wkt_lexer_116;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_102:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_102;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_102;
			if (yych == ' ') goto shapes_wkt_lexer_102;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_104;
			if (yych == 'Z') goto shapes_wkt_lexer_106;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_104;
			if (yych == 'z') goto shapes_wkt_lexer_106;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_104:
	++cursor;
	{ return WKT_LINESTRING_M_TAGGED_TEXT; }
shapes_wkt_lexer_106:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_117;
	if (yych == 'm') goto shapes_wkt_lexer_117;
	{ return WKT_LINESTRING_Z_TAGGED_TEXT; }
shapes_wkt_lexer_108:
	yych = *++cursor;
	if (yych == 'R') goto shapes_wkt_lexer_119;
	if (yych == 'r') goto shapes_wkt_lexer_119;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_109:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_109;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_109;
			if (yych == ' ') goto shapes_wkt_lexer_109;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_111;
			if (yych == 'Z') goto shapes_wkt_lexer_113;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_111;
			if (yych == 'z') goto shapes_wkt_lexer_113;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_111:
	++cursor;
	{ return WKT_MULTIPOINT_M_TAGGED_TEXT; }
shapes_wkt_lexer_113:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_120;
	if (yych == 'm') goto shapes_wkt_lexer_120;
	{ return WKT_MULTIPOINT_Z_TAGGED_TEXT; }
shapes_wkt_lexer_115:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_122;
	if (yych == 'n') goto shapes_wkt_lexer_122;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_116:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_124;
	if (yych == 'e') goto shapes_wkt_lexer_124;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_117:
	++cursor;
	{ return WKT_LINESTRING_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_119:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_125;
	if (yych == 'i') goto shapes_wkt_lexer_125;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_120:
	++cursor;
	{ return WKT_MULTIPOINT_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_122:
	yyaccept = 6;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_123;
			if (yych <= '\n') goto shapes_wkt_lexer_126;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_126;
			if (yych == ' ') goto shapes_wkt_lexer_126;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_128;
			if (yych == 'Z') goto shapes_wkt_lexer_130;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_128;
			if (yych == 'z') goto shapes_wkt_lexer_130;
		}
	}
shapes_wkt_lexer_123:
	{ return WKT_MULTIPOLYGON_TAGGED_TEXT; }
shapes_wkt_lexer_124:
	yych = *++cursor;
	if (yych == 'C') goto shapes_wkt_lexer_132;
	if (yych == 'c') goto shapes_wkt_lexer_132;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_125:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_133;
	if (yych == 'n') goto shapes_wkt_lexer_133;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_126:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_126;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_126;
			if (yych == ' ') goto shapes_wkt_lexer_126;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_128;
			if (yych == 'Z') goto shapes_wkt_lexer_130;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_128;
			if (yych == 'z') goto shapes_wkt_lexer_130;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_128:
	++cursor;
	{ return WKT_MULTIPOLYGON_M_TAGGED_TEXT; }
shapes_wkt_lexer_130:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_134;
	if (yych == 'm') goto shapes_wkt_lexer_134;
	{ return WKT_MULTIPOLYGON_Z_TAGGED_TEXT; }
shapes_wkt_lexer_132:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_136;
	if (yych == 't') goto shapes_wkt_lexer_136;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_133:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_137;
	if (yych == 'g') goto shapes_wkt_lexer_137;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_134:
	++cursor;
	{ return WKT_MULTIPOLYGON_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_136:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_139;
	if (yych == 'i') goto shapes_wkt_lexer_139;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_137:
	yyaccept = 7;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_138;
			if (yych <= '\n') goto shapes_wkt_lexer_140;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_140;
			if (yych == ' ') goto shapes_wkt_lexer_140;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_142;
			if (yych == 'Z') goto shapes_wkt_lexer_144;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_142;
			if (yych == 'z') goto shapes_wkt_lexer_144;
		}
	}
shapes_wkt_lexer_138:
	{ return WKT_MULTILINESTRING_TAGGED_TEXT; }
shapes_wkt_lexer_139:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_146;
	if (yych == 'o') goto shapes_wkt_lexer_146;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_140:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_140;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_140;
			if (yych == ' ') goto shapes_wkt_lexer_140;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_142;
			if (yych == 'Z') goto shapes_wkt_lexer_144;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_142;
			if (yych == 'z') goto shapes_wkt_lexer_144;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_142:
	++cursor;
	{ return WKT_MULTILINESTRING_M_TAGGED_TEXT; }
shapes_wkt_lexer_144:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_147;
	if (yych == 'm') goto shapes_wkt_lexer_147;
	{ return WKT_MULTILINESTRING_Z_TAGGED_TEXT; }
shapes_wkt_lexer_146:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_149;
	if (yych == 'n') goto shapes_wkt_lexer_149;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_147:
	++cursor;
	{ return WKT_MULTILINESTRING_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_149:
	yyaccept = 8;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_150;
			if (yych <= '\n') goto shapes_wkt_lexer_151;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_151;
			if (yych == ' ') goto shapes_wkt_lexer_151;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_153;
			if (yych == 'Z') goto shapes_wkt_lexer_155;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_153;
			if (yych == 'z') goto shapes_wkt_lexer_155;
		}
	}
shapes_wkt_lexer_150:
	{ return WKT_GEOMETRYCOLLECTION_TAGGED_TEXT; }
shapes_wkt_lexer_151:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_151;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_151;
			if (yych == ' ') goto shapes_wkt_lexer_151;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_153;
			if (yych == 'Z') goto shapes_wkt_lexer_155;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_153;
			if (yych == 'z') goto shapes_wkt_lexer_155;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_153:
	++cursor;
	{ return WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT; }
shapes_wkt_lexer_155:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_157;
	if (yych == 'm') goto shapes_wkt_lexer_157;
	{ return WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT; }
shapes_wkt_lexer_157:
	++cursor;
	{ return WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT; }
}

    }

    /*!
     * @brief returns the current token string
     * @return the token string
     *
     * @since 0.0.1
     */
    std::string get_token() const
    {
        return std::string(reinterpret_cast<const char*>(start), static_cast<size_t>(cursor - start));
    }

  private:
    /// pointer to the buffer
    const char* content = nullptr;

    /// pointer to the beginning of the current token
    const char* start = nullptr;

    /// pointer to the current token
    const char* cursor = nullptr;

    /// pointer to the end of the buffer
    const char* limit = nullptr;
};

}  // namespace shapes
}  // namespace simo