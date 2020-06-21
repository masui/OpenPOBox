//
// This file is created by "rklist2rkc -h ../romakana/rklist".  Don't edit!!
//
#ifdef PALM
#if SDK_VERSION >= 35
#include <PalmOS.h>
#else
#include <Pilot.h>
#endif
#include "ctype.h"
#endif
#include "romakana.h"

RomaKana *
InitRomaTable()
{
	RomaKana *rktable;
#ifdef UNIX
	rktable = (RomaKana*)malloc(sizeof(RomaKana)*238);
#endif
#ifdef PALM
	rktable = (RomaKana*)MemPtrNew(sizeof(RomaKana)*238);
#endif
	rktable[0].roma = ",";	rktable[0].kana = "\241\242";
	rktable[1].roma = "-";	rktable[1].kana = "\241\274";
	rktable[2].roma = ".";	rktable[2].kana = "\241\243";
	rktable[3].roma = "a";	rktable[3].kana = "\244\242";
	rktable[4].roma = "ba";	rktable[4].kana = "\244\320";
	rktable[5].roma = "be";	rktable[5].kana = "\244\331";
	rktable[6].roma = "bi";	rktable[6].kana = "\244\323";
	rktable[7].roma = "bo";	rktable[7].kana = "\244\334";
	rktable[8].roma = "bu";	rktable[8].kana = "\244\326";
	rktable[9].roma = "bya";	rktable[9].kana = "\244\323\244\343";
	rktable[10].roma = "bye";	rktable[10].kana = "\244\323\244\247";
	rktable[11].roma = "byi";	rktable[11].kana = "\244\323\244\243";
	rktable[12].roma = "byo";	rktable[12].kana = "\244\323\244\347";
	rktable[13].roma = "byu";	rktable[13].kana = "\244\323\244\345";
	rktable[14].roma = "ca";	rktable[14].kana = "\244\253";
	rktable[15].roma = "ce";	rktable[15].kana = "\244\273";
	rktable[16].roma = "cha";	rktable[16].kana = "\244\301\244\343";
	rktable[17].roma = "che";	rktable[17].kana = "\244\301\244\247";
	rktable[18].roma = "chi";	rktable[18].kana = "\244\301";
	rktable[19].roma = "cho";	rktable[19].kana = "\244\301\244\347";
	rktable[20].roma = "chu";	rktable[20].kana = "\244\301\244\345";
	rktable[21].roma = "ci";	rktable[21].kana = "\244\267";
	rktable[22].roma = "co";	rktable[22].kana = "\244\263";
	rktable[23].roma = "cu";	rktable[23].kana = "\244\257";
	rktable[24].roma = "cya";	rktable[24].kana = "\244\301\244\343";
	rktable[25].roma = "cye";	rktable[25].kana = "\244\301\244\247";
	rktable[26].roma = "cyi";	rktable[26].kana = "\244\301\244\243";
	rktable[27].roma = "cyo";	rktable[27].kana = "\244\301\244\347";
	rktable[28].roma = "cyu";	rktable[28].kana = "\244\301\244\345";
	rktable[29].roma = "da";	rktable[29].kana = "\244\300";
	rktable[30].roma = "de";	rktable[30].kana = "\244\307";
	rktable[31].roma = "dha";	rktable[31].kana = "\244\307\244\343";
	rktable[32].roma = "dhe";	rktable[32].kana = "\244\307\244\247";
	rktable[33].roma = "dhi";	rktable[33].kana = "\244\307\244\243";
	rktable[34].roma = "dho";	rktable[34].kana = "\244\307\244\347";
	rktable[35].roma = "dhu";	rktable[35].kana = "\244\307\244\345";
	rktable[36].roma = "di";	rktable[36].kana = "\244\302";
	rktable[37].roma = "do";	rktable[37].kana = "\244\311";
	rktable[38].roma = "du";	rktable[38].kana = "\244\305";
	rktable[39].roma = "dya";	rktable[39].kana = "\244\302\244\343";
	rktable[40].roma = "dye";	rktable[40].kana = "\244\302\244\247";
	rktable[41].roma = "dyi";	rktable[41].kana = "\244\302\244\243";
	rktable[42].roma = "dyo";	rktable[42].kana = "\244\302\244\347";
	rktable[43].roma = "dyu";	rktable[43].kana = "\244\307\244\345";
	rktable[44].roma = "e";	rktable[44].kana = "\244\250";
	rktable[45].roma = "fa";	rktable[45].kana = "\244\325\244\241";
	rktable[46].roma = "fe";	rktable[46].kana = "\244\325\244\247";
	rktable[47].roma = "fi";	rktable[47].kana = "\244\325\244\243";
	rktable[48].roma = "fo";	rktable[48].kana = "\244\325\244\251";
	rktable[49].roma = "fu";	rktable[49].kana = "\244\325";
	rktable[50].roma = "ga";	rktable[50].kana = "\244\254";
	rktable[51].roma = "ge";	rktable[51].kana = "\244\262";
	rktable[52].roma = "gi";	rktable[52].kana = "\244\256";
	rktable[53].roma = "go";	rktable[53].kana = "\244\264";
	rktable[54].roma = "gu";	rktable[54].kana = "\244\260";
	rktable[55].roma = "gwa";	rktable[55].kana = "\244\260\244\241";
	rktable[56].roma = "gwe";	rktable[56].kana = "\244\260\244\247";
	rktable[57].roma = "gwi";	rktable[57].kana = "\244\260\244\243";
	rktable[58].roma = "gwo";	rktable[58].kana = "\244\260\244\251";
	rktable[59].roma = "gwu";	rktable[59].kana = "\244\260";
	rktable[60].roma = "gya";	rktable[60].kana = "\244\256\244\343";
	rktable[61].roma = "gye";	rktable[61].kana = "\244\256\244\247";
	rktable[62].roma = "gyi";	rktable[62].kana = "\244\256\244\243";
	rktable[63].roma = "gyo";	rktable[63].kana = "\244\256\244\347";
	rktable[64].roma = "gyu";	rktable[64].kana = "\244\256\244\345";
	rktable[65].roma = "ha";	rktable[65].kana = "\244\317";
	rktable[66].roma = "he";	rktable[66].kana = "\244\330";
	rktable[67].roma = "hi";	rktable[67].kana = "\244\322";
	rktable[68].roma = "ho";	rktable[68].kana = "\244\333";
	rktable[69].roma = "hu";	rktable[69].kana = "\244\325";
	rktable[70].roma = "hya";	rktable[70].kana = "\244\322\244\343";
	rktable[71].roma = "hye";	rktable[71].kana = "\244\322\244\247";
	rktable[72].roma = "hyi";	rktable[72].kana = "\244\322\244\243";
	rktable[73].roma = "hyo";	rktable[73].kana = "\244\322\244\347";
	rktable[74].roma = "hyu";	rktable[74].kana = "\244\322\244\345";
	rktable[75].roma = "i";	rktable[75].kana = "\244\244";
	rktable[76].roma = "ja";	rktable[76].kana = "\244\270\244\343";
	rktable[77].roma = "je";	rktable[77].kana = "\244\270\244\247";
	rktable[78].roma = "ji";	rktable[78].kana = "\244\270";
	rktable[79].roma = "jo";	rktable[79].kana = "\244\270\244\347";
	rktable[80].roma = "ju";	rktable[80].kana = "\244\270\244\345";
	rktable[81].roma = "jya";	rktable[81].kana = "\244\270\244\343";
	rktable[82].roma = "jye";	rktable[82].kana = "\244\270\244\247";
	rktable[83].roma = "jyi";	rktable[83].kana = "\244\270\244\243";
	rktable[84].roma = "jyo";	rktable[84].kana = "\244\270\244\347";
	rktable[85].roma = "jyu";	rktable[85].kana = "\244\270\244\345";
	rktable[86].roma = "ka";	rktable[86].kana = "\244\253";
	rktable[87].roma = "ke";	rktable[87].kana = "\244\261";
	rktable[88].roma = "ki";	rktable[88].kana = "\244\255";
	rktable[89].roma = "ko";	rktable[89].kana = "\244\263";
	rktable[90].roma = "ku";	rktable[90].kana = "\244\257";
	rktable[91].roma = "kwa";	rktable[91].kana = "\244\257\244\356";
	rktable[92].roma = "kwe";	rktable[92].kana = "\244\257\244\247";
	rktable[93].roma = "kwi";	rktable[93].kana = "\244\257\244\243";
	rktable[94].roma = "kwo";	rktable[94].kana = "\244\257\244\251";
	rktable[95].roma = "kwu";	rktable[95].kana = "\244\257";
	rktable[96].roma = "kya";	rktable[96].kana = "\244\255\244\343";
	rktable[97].roma = "kye";	rktable[97].kana = "\244\255\244\247";
	rktable[98].roma = "kyi";	rktable[98].kana = "\244\255\244\243";
	rktable[99].roma = "kyo";	rktable[99].kana = "\244\255\244\347";
	rktable[100].roma = "kyu";	rktable[100].kana = "\244\255\244\345";
	rktable[101].roma = "la";	rktable[101].kana = "\244\241";
	rktable[102].roma = "le";	rktable[102].kana = "\244\247";
	rktable[103].roma = "li";	rktable[103].kana = "\244\243";
	rktable[104].roma = "lo";	rktable[104].kana = "\244\251";
	rktable[105].roma = "lu";	rktable[105].kana = "\244\245";
	rktable[106].roma = "lwa";	rktable[106].kana = "\244\356";
	rktable[107].roma = "lya";	rktable[107].kana = "\244\343";
	rktable[108].roma = "lye";	rktable[108].kana = "\244\247";
	rktable[109].roma = "lyi";	rktable[109].kana = "\244\243";
	rktable[110].roma = "lyo";	rktable[110].kana = "\244\347";
	rktable[111].roma = "lyu";	rktable[111].kana = "\244\345";
	rktable[112].roma = "ma";	rktable[112].kana = "\244\336";
	rktable[113].roma = "me";	rktable[113].kana = "\244\341";
	rktable[114].roma = "mi";	rktable[114].kana = "\244\337";
	rktable[115].roma = "mo";	rktable[115].kana = "\244\342";
	rktable[116].roma = "mu";	rktable[116].kana = "\244\340";
	rktable[117].roma = "mya";	rktable[117].kana = "\244\337\244\343";
	rktable[118].roma = "mye";	rktable[118].kana = "\244\337\244\247";
	rktable[119].roma = "myi";	rktable[119].kana = "\244\337\244\243";
	rktable[120].roma = "myo";	rktable[120].kana = "\244\337\244\347";
	rktable[121].roma = "myu";	rktable[121].kana = "\244\337\244\345";
	rktable[122].roma = "n'";	rktable[122].kana = "\244\363";
	rktable[123].roma = "na";	rktable[123].kana = "\244\312";
	rktable[124].roma = "ne";	rktable[124].kana = "\244\315";
	rktable[125].roma = "ni";	rktable[125].kana = "\244\313";
	rktable[126].roma = "no";	rktable[126].kana = "\244\316";
	rktable[127].roma = "nu";	rktable[127].kana = "\244\314";
	rktable[128].roma = "nya";	rktable[128].kana = "\244\313\244\343";
	rktable[129].roma = "nye";	rktable[129].kana = "\244\313\244\247";
	rktable[130].roma = "nyi";	rktable[130].kana = "\244\313\244\243";
	rktable[131].roma = "nyo";	rktable[131].kana = "\244\313\244\347";
	rktable[132].roma = "nyu";	rktable[132].kana = "\244\313\244\345";
	rktable[133].roma = "o";	rktable[133].kana = "\244\252";
	rktable[134].roma = "pa";	rktable[134].kana = "\244\321";
	rktable[135].roma = "pe";	rktable[135].kana = "\244\332";
	rktable[136].roma = "pi";	rktable[136].kana = "\244\324";
	rktable[137].roma = "po";	rktable[137].kana = "\244\335";
	rktable[138].roma = "pu";	rktable[138].kana = "\244\327";
	rktable[139].roma = "pya";	rktable[139].kana = "\244\324\244\343";
	rktable[140].roma = "pye";	rktable[140].kana = "\244\324\244\247";
	rktable[141].roma = "pyi";	rktable[141].kana = "\244\324\244\243";
	rktable[142].roma = "pyo";	rktable[142].kana = "\244\324\244\347";
	rktable[143].roma = "pyu";	rktable[143].kana = "\244\324\244\345";
	rktable[144].roma = "qa";	rktable[144].kana = "\244\257\244\241";
	rktable[145].roma = "qe";	rktable[145].kana = "\244\257\244\247";
	rktable[146].roma = "qi";	rktable[146].kana = "\244\257\244\243";
	rktable[147].roma = "qo";	rktable[147].kana = "\244\257\244\251";
	rktable[148].roma = "qu";	rktable[148].kana = "\244\257";
	rktable[149].roma = "qya";	rktable[149].kana = "\244\257\244\343";
	rktable[150].roma = "qye";	rktable[150].kana = "\244\257\244\247";
	rktable[151].roma = "qyi";	rktable[151].kana = "\244\257\244\243";
	rktable[152].roma = "qyo";	rktable[152].kana = "\244\257\244\347";
	rktable[153].roma = "qyu";	rktable[153].kana = "\244\257\244\345";
	rktable[154].roma = "ra";	rktable[154].kana = "\244\351";
	rktable[155].roma = "re";	rktable[155].kana = "\244\354";
	rktable[156].roma = "ri";	rktable[156].kana = "\244\352";
	rktable[157].roma = "ro";	rktable[157].kana = "\244\355";
	rktable[158].roma = "ru";	rktable[158].kana = "\244\353";
	rktable[159].roma = "rya";	rktable[159].kana = "\244\352\244\343";
	rktable[160].roma = "rye";	rktable[160].kana = "\244\352\244\247";
	rktable[161].roma = "ryi";	rktable[161].kana = "\244\352\244\243";
	rktable[162].roma = "ryo";	rktable[162].kana = "\244\352\244\347";
	rktable[163].roma = "ryu";	rktable[163].kana = "\244\352\244\345";
	rktable[164].roma = "sa";	rktable[164].kana = "\244\265";
	rktable[165].roma = "se";	rktable[165].kana = "\244\273";
	rktable[166].roma = "sha";	rktable[166].kana = "\244\267\244\343";
	rktable[167].roma = "she";	rktable[167].kana = "\244\267\244\247";
	rktable[168].roma = "shi";	rktable[168].kana = "\244\267";
	rktable[169].roma = "sho";	rktable[169].kana = "\244\267\244\347";
	rktable[170].roma = "shu";	rktable[170].kana = "\244\267\244\345";
	rktable[171].roma = "si";	rktable[171].kana = "\244\267";
	rktable[172].roma = "so";	rktable[172].kana = "\244\275";
	rktable[173].roma = "su";	rktable[173].kana = "\244\271";
	rktable[174].roma = "sya";	rktable[174].kana = "\244\267\244\343";
	rktable[175].roma = "sye";	rktable[175].kana = "\244\267\244\247";
	rktable[176].roma = "syi";	rktable[176].kana = "\244\267\244\243";
	rktable[177].roma = "syo";	rktable[177].kana = "\244\267\244\347";
	rktable[178].roma = "syu";	rktable[178].kana = "\244\267\244\345";
	rktable[179].roma = "ta";	rktable[179].kana = "\244\277";
	rktable[180].roma = "te";	rktable[180].kana = "\244\306";
	rktable[181].roma = "tha";	rktable[181].kana = "\244\306\244\343";
	rktable[182].roma = "the";	rktable[182].kana = "\244\306\244\247";
	rktable[183].roma = "thi";	rktable[183].kana = "\244\306\244\243";
	rktable[184].roma = "tho";	rktable[184].kana = "\244\306\244\347";
	rktable[185].roma = "thu";	rktable[185].kana = "\244\306\244\345";
	rktable[186].roma = "ti";	rktable[186].kana = "\244\301";
	rktable[187].roma = "to";	rktable[187].kana = "\244\310";
	rktable[188].roma = "tsa";	rktable[188].kana = "\244\304\244\241";
	rktable[189].roma = "tse";	rktable[189].kana = "\244\304\244\247";
	rktable[190].roma = "tsi";	rktable[190].kana = "\244\304\244\243";
	rktable[191].roma = "tso";	rktable[191].kana = "\244\304\244\251";
	rktable[192].roma = "tsu";	rktable[192].kana = "\244\304";
	rktable[193].roma = "tu";	rktable[193].kana = "\244\304";
	rktable[194].roma = "tya";	rktable[194].kana = "\244\301\244\343";
	rktable[195].roma = "tye";	rktable[195].kana = "\244\301\244\247";
	rktable[196].roma = "tyi";	rktable[196].kana = "\244\301\244\243";
	rktable[197].roma = "tyo";	rktable[197].kana = "\244\301\244\347";
	rktable[198].roma = "tyu";	rktable[198].kana = "\244\301\244\345";
	rktable[199].roma = "u";	rktable[199].kana = "\244\246";
	rktable[200].roma = "va";	rktable[200].kana = "\244\364\244\241";
	rktable[201].roma = "ve";	rktable[201].kana = "\244\364\244\247";
	rktable[202].roma = "vi";	rktable[202].kana = "\244\364\244\243";
	rktable[203].roma = "vo";	rktable[203].kana = "\244\364\244\251";
	rktable[204].roma = "vu";	rktable[204].kana = "\244\364";
	rktable[205].roma = "wa";	rktable[205].kana = "\244\357";
	rktable[206].roma = "we";	rktable[206].kana = "\244\246\244\247";
	rktable[207].roma = "wi";	rktable[207].kana = "\244\246\244\243";
	rktable[208].roma = "wo";	rktable[208].kana = "\244\362";
	rktable[209].roma = "wu";	rktable[209].kana = "\244\246";
	rktable[210].roma = "xa";	rktable[210].kana = "\244\241";
	rktable[211].roma = "xe";	rktable[211].kana = "\244\247";
	rktable[212].roma = "xi";	rktable[212].kana = "\244\243";
	rktable[213].roma = "xo";	rktable[213].kana = "\244\251";
	rktable[214].roma = "xtsu";	rktable[214].kana = "\244\303";
	rktable[215].roma = "xtu";	rktable[215].kana = "\244\303";
	rktable[216].roma = "xu";	rktable[216].kana = "\244\245";
	rktable[217].roma = "xwa";	rktable[217].kana = "\244\356";
	rktable[218].roma = "xya";	rktable[218].kana = "\244\343";
	rktable[219].roma = "xye";	rktable[219].kana = "\244\247";
	rktable[220].roma = "xyi";	rktable[220].kana = "\244\243";
	rktable[221].roma = "xyo";	rktable[221].kana = "\244\347";
	rktable[222].roma = "xyu";	rktable[222].kana = "\244\345";
	rktable[223].roma = "ya";	rktable[223].kana = "\244\344";
	rktable[224].roma = "ye";	rktable[224].kana = "\244\244\244\247";
	rktable[225].roma = "yi";	rktable[225].kana = "\244\244";
	rktable[226].roma = "yo";	rktable[226].kana = "\244\350";
	rktable[227].roma = "yu";	rktable[227].kana = "\244\346";
	rktable[228].roma = "za";	rktable[228].kana = "\244\266";
	rktable[229].roma = "ze";	rktable[229].kana = "\244\274";
	rktable[230].roma = "zi";	rktable[230].kana = "\244\270";
	rktable[231].roma = "zo";	rktable[231].kana = "\244\276";
	rktable[232].roma = "zu";	rktable[232].kana = "\244\272";
	rktable[233].roma = "zya";	rktable[233].kana = "\244\270\244\343";
	rktable[234].roma = "zye";	rktable[234].kana = "\244\270\244\247";
	rktable[235].roma = "zyi";	rktable[235].kana = "\244\270\244\243";
	rktable[236].roma = "zyo";	rktable[236].kana = "\244\270\244\347";
	rktable[237].roma = "zyu";	rktable[237].kana = "\244\270\244\345";
	return rktable;
}

int
Roma2Kana(unsigned char *roma, unsigned char *kana, RomaKana *rktable)
{
	RomaKana *rk;
	int i,len;
	unsigned char buf[50],*r;
	int okay = 1;

	StrCopy(buf,roma);
	for(r=buf;*r;r++){
		if(IsUpper(*r)) *r = ToLower(*r);
	}
	r = buf;
	*kana = '\0';
	while(*r){
		for(i=0;i<238;i++){
			rk = rktable+i;
			len = StrLen(rk->roma);
			if(StrNCompare(r,rk->roma,len)==0){
				StrCat(kana,rk->kana);
				r += len;
				break;
			}
		}
		if(i >= 238){
			if(*r == 'n' && StrChr("bcdfghjklmnpqrstvwxz",*(r+1))){
				StrCat(kana,"\244\363");
				r++;
			}
			else if(StrChr("bcdfghjklmpqrstvwxyz",*r) && *r == *(r+1)){
				StrCat(kana,"\244\303");
				r++;
			}
			else if(*r == 'n' && ! *(r+1)){
				StrCat(kana,"\244\363");
				r++;
			}
			else {
				len = StrLen(kana);
				kana[len] = *r;
				kana[len+1] = '\0';
		      		r++;
				okay = 0;
			}
		}
	}
	return okay;
}
