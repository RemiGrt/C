#include "ast.h"

int compteurLabel=0;
int compteurEtapes=0;

nodeType *createNumericNode(float v)
{
	nodeType *p;

	if ((p=(nodeType*)malloc(sizeof(nodeType))) == NULL)
	{
		printf("out of memory error\n");
		exit(1);
	}

	p->type=typeNumeric;
	p->t_numeric.valeur=v;
	
	return p;
}

nodeType *createOperatorNode(int oper, int nops, ...) 
{
    	va_list ap;
    	nodeType *p;
    	int i;

    	/* allocate node */
    	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
	{
		printf("out of memory error\n");
		exit(1);
	}
    	if ((p->t_oper.op = (nodeType**)malloc(nops * sizeof(nodeType))) == NULL)
	{
		printf("out of memory error\n");
		exit(1);
	}

    	/* copy information */
    	p->type = typeOperator;
    	p->t_oper.oper = oper;
    	p->t_oper.nOperands = nops;
    	va_start(ap, nops);
    	for (i = 0; i < nops; i++)
        	p->t_oper.op[i] = va_arg(ap, nodeType*);
    	va_end(ap);
    	return p;
}

nodeType *createIdentifierNode(char *id,int flag)
{
        nodeType *p;

        if ((p=malloc(sizeof(nodeType))) == NULL)
        {
                printf("out of memory error\n");
                exit(1);
        }

        p->type=typeIdentifier;
        p->t_identifier.ident=strdup(id);
	p->t_identifier.flag=flag;
	if (strncmp(p->t_identifier.ident,"but",3)==0)
		p->t_identifier.key=KEY_BUTTON;
	else if (strncmp(p->t_identifier.ident,"ana",3)==0)
		p->t_identifier.key=KEY_ANA;
	else if (strncmp(p->t_identifier.ident,"tor",3)==0)
		p->t_identifier.key=KEY_TOR;
	else if (strncmp(p->t_identifier.ident,"pwm",3)==0)
		p->t_identifier.key=KEY_PWM;
	else
		p->t_identifier.key=KEY_IDENT;

        return p;
}

void generateAsmExpression(nodeType *n, FILE *fout)
{
        if (n==NULL)
                return;

        switch (n->type)
        {
                case typeNumeric:
                        {
                                fprintf(fout,"\tpushi\t%d\n",n->t_numeric.valeur);
                        }
                        break;
                case typeIdentifier:
                        {
				if (strncmp(n->t_identifier.ident,"but0",4)==0)
				{
					if (n->t_identifier.flag==0)
						fprintf(fout,"\tpush\t0\n");
					else if (n->t_identifier.flag==1)
						fprintf(fout,"\tpush\t1\n");
					else if (n->t_identifier.flag==2)
						fprintf(fout,"\tpush\t2\n");
				}
				else if (strncmp(n->t_identifier.ident,"but1",4)==0)
				{
					if (n->t_identifier.flag==0)
						fprintf(fout,"\tpush\t3\n");
					else if (n->t_identifier.flag==1)
						fprintf(fout,"\tpush\t4\n");
					else if (n->t_identifier.flag==2)
						fprintf(fout,"\tpush\t5\n");
				}
				else if (strncmp(n->t_identifier.ident,"ana0",4)==0)
				{
					fprintf(fout,"\tpush\t6\n");
				}
				else if (strncmp(n->t_identifier.ident,"ana1",4)==0)
				{
					fprintf(fout,"\tpush\t7\n");
				}
			}
                        break;
                case typeOperator:
                        {
                                switch (n->t_oper.oper)
                                {
                                        case OPER_ADD:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tadd\n");
                                                break;
                                        case OPER_SUB:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tsub\n");
                                                break;
                                        case OPER_MULT:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tmult\n");
                                                break;
                                        case OPER_DIV:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tdiv\n");
                                                break;
                                        case OPER_AND:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tand\n");
                                                break;
                                        case OPER_OR:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tor\n");
                                                break;
                                        case OPER_NOT:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                fprintf(fout,"\tnot\n");
                                                break;
                                        case OPER_INF:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tls\n");
                                                break;
                                        case OPER_SUP:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tgt\n");
                                                break;
                                        case OPER_EQ:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\teq\n");
                                                break;
                                        case OPER_NE:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\teq\n");
                                                fprintf(fout,"\tnot\n");
                                                break;
                                        case OPER_SEQUENCE:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                break;
                                        default:
                                                break;
                                }
                        }
                        break;
        }
}

void grafcet_interpreter()
{
	char buf[256];
	int but0,but1,an0,an1,oldbut0,oldbut1,risebut0,risebut1,fallbut0,fallbut1;
	oldbut0=0;
	oldbut1=0;

	while (1)
	{
		sscanf(buf,"%d:%d:%d:%d",&but0,&but1,&an0,&an1);
		if ((oldbut0==0) && (but0==1))
			risebut0=1;
		else
			risebut0=0;
		if ((oldbut1==0) && (but1==1))
			risebut1=1;
		else
			risebut1=0;

		if ((oldbut0==1) && (but0==0))
			fallbut0=1;
		else
			fallbut0=0;
		if ((oldbut1==1) && (but1==0))
			fallbut1=1;
		else
			fallbut1=0;

		//printf("but0=%d but1=%d an0=%d an1=%d\n",but0,but1,an0,an1);
		if (risebut0)
			printf("risebut0\n");
		if (risebut1)
			printf("risebut1\n");
		if (fallbut0)
	ƒMŠmƒíÕ¤mö·Ç®W‰\y?%È‡«—^©œ¤“ddìmã\[lêF!BÜ¨üÑĞÖ#î¶x0¶ÙÌWım}á§V:ìôÃŞJJ¡¸MØàòÈa\¾Ã„|3~}[(XØÖÔqŠ¼iA$Hµ°%sÕ?v“ƒ Ù»ÏÑ¡PÉÊïóR"l«³õµ<½ÒÏ}”AmT=g½h®¾?Ã~V¹1èÄdR¯,3BTóB¢Ü7õˆãŸĞ2@-‰½óÑŞ¬?<Vˆa!GMØf`¢ ‹#jl	o;µMÄ È5¸ÒÂ5aM¡fæiDÙF,yçBj·±‚;4¼»QqMU•¤²ëøpÏhw{{=»ä™bÅs/œ.%`ÂĞnÜÏvLÔ¼sŸ|zïg"LWL•x'­1fØd Ÿ—AŒ›á$4_«I%Û¸Ù22{ñâm©ªÓÀ©(l°±rŞ*$1‰…o'És$^2¦q&
%Ö+.UÓİ(25¯ÚmKTkH?7ÙW—Mæx"YÀ+næ°ƒg¸wz/3©v´T«Ûz€~­»³…Çl<Ş,MàW±W>Ñ)Fö'¤ò»~lp<SõE–šC¾‰!uE¯…bzàÿRº1ÀËwè‰ÖêŸÀçYıxÔİ™Ğ¨4Ş_*ÜpCsˆÉ×óW¼pqµšKiO¶Ã63•EÕö­ta*0m0Îo»¡È…ÛVÒÑ*%¨ Íï<½ªñô+ÒÑ€Ş&‡Ã!æœLÅSá‘[g³‚l½¸ÀfBhU;S7Ró`I7R–)¶LDMëjló?Ìµ!V·;Q›ÇÛ-\õG´Ö¥Ø±~‰:ëc:7i«~Df-JÄC"…7´+Ípÿ‡p0Ñü+´ßXÛ_^Ä}Ì¡Ñ³ÍEöF¢rT‹zˆ?†Í”Æe#ˆË/–¬|^Q.s0ÕzlşœD~$Àg¤v{k!SIëº¹‡Ö¡QéKG/ş‚÷¶|§±S²^™W—óYãüFË¼g„@qÃÈ6¹À—Şu"Å%åäP‡qql™Fzpÿ™øÚ‘¸ÎãÒ@¼ôÍ¾ëŸó$çŞĞ:¢ı
*‰6+äwê ¨â•¨ı’™§A5““d¾¤Òa"»2\½ÛR+ãûMÖdFÖŒów=u‰İÎW/å¡¿†c9Ö€7¤’6ºgÛO°×wĞû3pÆÈíÉ¡ß@µµæÄlbÃj/«ç¦ã:OPY«Ôèq”bUôö(÷‘ò5¤ÓA;Ìw	.Î—¥9ò<|•İG°ßÉ:B}ô²Åà 8‘>‘1a{{
1û©a½öû5ƒ1™ÑÔ]ŸŞGĞ6¬Ép}£v<ú°=kÔ
h¶e.mc²u²ˆêĞÎ®?§¿¹Â&½½lw0âh‰Ï¸SµéºÆ:A%‘Ç«f{Æ‹$Ü¶[#>.xgl4K”±æaî6ÓÆ¥y¹smÑ…\€x[dZ«î3¶¦­#›Šü÷O–ÚtK$+(qû²¼?‡-Íá¶Kòõ±5è1@WÃZ;Şô`Z,¾'7Ù˜ñHÜ0E<T²ˆlóÁfª†§ãµÿ	àÇ%s]Ä/Çtà!Â6ıš—³6‘ş¢+~(gŠ.µdù¯-Àq‹Á*õ(uœ€q9=…3qÑÎT»ëy¨6d+
©»YÒT¢^8qpÂ94«§óùo¬I¬7}±Äo×QæóßN^­#(ß ¢œ3Œ¢N—¨‰>`áRŠÚùœZƒ3)NîG­ò¶óÎÛ½e´>¶”i–`MÅŸrãZ˜ÒL|àõ}Jø80Ğ•ıãCilÛİó İ9×>áü†.Zşğé»j™àŒÏ69FöŠtÊg¦Ô…°=€WCU_fA¯²¹,ÃC]„$±üuã|q¡\c-ÍiÕPvûùÜ\ó §B{\ÍÒ€Iå¡¸V¿÷­ó¹oŸ–ÙAkÏ_Ø	-İã³ÎÌÒš§S©ëÖ6A€ØÆh†â0+X~±ìaêC{ë˜Lh»I;Î¹qé>€(û1û[~¡\¦4S9y:g‡ \°òÏ{»’çïQˆ@„¡yĞÀ¼©áb¦êñ`` ú`Í›0ÆxÊˆ†¥Aµ*ëÑ
óošÛB±(Àñ)¦·º²³ÿ'ëxãøHfÒÒnn´*†ó6uA“ë_›hµËÑäró˜éÔÌCSóH‹ö<¬oj`º=ûş`lT÷İ J²q§2Ñ¼çÕÙç™=Cz`?(Bá2{è;b[ZÛ¼¨RëïÇËØ3İH>øéõ°.›
î°b0A¨
³–FêìpCİ·”Ç/#±Ú4¯j6Â´ìÚx‡Ö[DÆ~dˆ:½èñåºÚÒŒÚÏóÊ
ã™‹±C$È£ßÄÕ„X2²âÁæt
…Olÿâ-ŞFEc©—ù”T©"~¨i,TÉ~V0İ$Š³íPO8fÂ]ğı5 m•½k‘ânÅßkrÓ…àñ‘K¬ióƒ¤eØFLueÍchCÅ4€VÕiì/{Èl2¥O¢Yy;7
Ì–Ô ŞF^aœ-È:)gÇÉÒ­ôVê;SğÏĞ›Vû”DºŒñm.`¦¢ÙÑ8Ñ#käH'I]zÓÅŞfÃX<‹/@rQ§=Ë6¤dº®ˆdá›.vÃR° ²ç5f0ƒœp¸U Ÿûw¿Ùu¸ÿ¥ƒDB–qÀš1Î*Ú§ ğ*oFÕÉ<W§hcš[#b¿İ§ïõé¹”‚pRh;¤›9J¯t.‚Îde-+Vä+­Gº¡bŸ´àl÷Éµ…º–óÛ³=M"Ï‹^ÈíÉÄ:¿…Ø¯Ï:óöİ/èV<¶M¿Ú©jĞcK}ñY­tÉİ$¡†‘s‹d3»>ºF´ÑÑº[9ªZ•±®æìºıKãÔ”ï šï ¢²ààk*3q‰ 2Qdhj®ÀAt×ÛFœöQä‚=Aª¨%ÛÂM‹èkuA¬ã0F8¦Œ?]«¢]Á	.İü_ª`3Iº{î$	J\=íN]M¥ {$lmpApV„Áï'²ìÄ^à;jq/[éDZ'÷Œ¶È•šcƒÓB¤»ş®$©‡–/Å/UçvT{¶I&U½±÷?ˆïéÀ´Ê¶¶3(Ğ*RıktS‘R<:Æµô»ŒCb0Ïqÿ'ö#º÷Zi’w»ãÂPÏÉAá4æ°·Ä"‡€µ³“fsì-j¼ï`îÉÓ7a< ½µ±K´£†æfnê’]„í0ÆEqHsT×w2,-d|ŸÕó¼PöÔ$7Òwê×ÀµcIv£jƒ¦ç1™¬òcLÁ*l7 şøSlàØÌ ‹……I½wúMRËöú2t'bQÄ7¹¬½{‡	ßçaª6ådSìÉ#r5vÖ=iWe=ü}xZ~•YÃXã7÷õ‡ÃHÙŸ¯zNÂ.ÜñöPÒ¼%D2Ú$¢Ú ÉI.ÆŸ¸ÌQÈ©y7=;£Ô@.\³5…™œ§ûU]¢JöC1€×"ŒÀKÕ¡šY&&·„Ğÿ˜:Hœ×²(GµöH¹s¤T@İ¬…•š«™šf~¬¹^J9ó Ñ'ª	Š+^¦ óÕGŸ#õB®ZÄGvÍb™`eA(J³Ú‚‘\})d¹·Gú4nƒhÆÖª.e ä½È5®Æ7T©7à2:0¬ÕÑâ%ÑÊçMÖ×7wgØÎsÊ,æ¶æº@5~Â+†Y¥‘3x:dK›àº¿ÒØv©üÌ}"_Ñ{·C÷m` R;_÷Hñ.Ÿ\ŠË¯»hX>RÒ,ß½÷39(“¡ŒQ_½H3‘!éçãô·üÿ<ë}Å‘!#Ç´®.úLQó`K¨ÛCbvxSÛ;62Ó–ÎÎ™}z†½s~:Ö[{¶{61ú(cöî. %E.
ÜZGT<õu'$ÒL‚BÇúÿÌ`]KC.u~{ìRVŸ'4æ1*rS`^¹Ä¿6Ä°âÒÁÓïˆÅÏ®ZÍ¢ñØT¸2äÔw¦D+Œf//‡tQ/U@S´;ıpÄK¾-~F¦ÃS¶0n™r"CeıØö~6ÙÀÀ‡‡¡gP:E0³uß}l„İñõ×âLì}ÁBBc¢$}
|Ÿ¢n)‡,÷v´êKdéu7³W8’Ét¿Rµ.´bTx#è~rÈÑ¤Zñˆ©¹ÒHrqHo“†)wË¿R5_oˆ •GDÕİGAÄ˜Sù±ùş‰mçÁˆ™å¨£2J’¨©˜Øºõ@
/S„÷ğ0Ÿ,°ê5İVd`Œ/Ò®ËPM#¹Á”Ö’x4Ÿ/E±èØŠ‘`±d*é2K«‚ì|tµ’C£©3Ï- -ò†>Ò­xÃ‡sÆ,<p¡‚h1nî]€¢A#ë)RlU):«¿	ûò}jÆlÓÒù-µË9?ĞŠ+£M¥{$Âû%¢øË„Õïe±É­ÓÏ9éxµÜd1I®r~B‹Åp÷ŸÁ¾ßÜâ2¬B*á¯„÷E¿´Œ-<Öeç;}´£&é:	é¹€LŸ÷¤¨ÕÇãSiy»7a§i3¯r1Ÿê¢^ò¥-¦ôÌÕÆoUG}Äø#üªÈ/Âp	¶ää)\G½®!¥ùÂH~B ÕdVçÛ@Ûj‰› Å>‰l÷*®iÕÚM@-NWa$·ØoÂú¸Fµ÷EE@óÙWGtïaÜèÔmü8ûö˜·(”ZoŠ/éÓŸ,xtñ–¡§d	û\ÑFDY½(”Â'äA·¹D"+B÷¤§ğ*îb|Òg ßeñK®½V–Ç~uó&ìM%[è%•è·5.æWŠM?J§o@øËãíƒ§ÔxfÔ9kÂ~LıZ òV‚@X”AŠÍ|ÄKy?ßí¸Ò^(®‰J.”ùˆz€M Oˆb<8tO©Ï+¯cÜ0avıQĞ¶}í:ëqI-§óòBX›ı¤™	J¢Ÿ!(¼ú$0ÊçN[/$EŠ‘“ırL"ÔHnó!Ú‹,Ö¸0ùkÈçø‡£änÓØ!¤b½¨“ÌáS’¡¡³aò -¿*‡Öá¯Ac¦=m›\¼˜s	ée¸¸:Õj»–<ºÂ.A‹œCíù¦Aš5¼a.ªçİ+ÆFDg*-w'èQgwI{ôİÜ~'
-2ñö}¤.«Î2ÉUî·×Ma§ÀœòOMjUl?•™ç¶s*SğÇÙ§êQê^eÊmcÖ]ĞwÇ@_0¿«<uÒ*7—ÑkEBÂ´İ:ú–Œˆ÷Ä­D¥w½Í¡@œIÈd¹Wã—²æöWMŸ”İ0ã5Bv­óÜ©e›q$;ÄÏ‘z'øÆËñ‚=Õo€O1¿€‡i¡©2“íô²à·AOééóªr–—ÉX¤Dè`˜ë‰ù-BGÄzëCÄ&Ñ¸#ßFê
RèvÊ}0Š]ß±jÖåcüæ YÿaØQƒ!YI†+Vk5¬”ş4~FÏİŒ7¾0jİ€†H°ÜîTÜa©:(•+Œ99©Ë|¼Çøı¾Û;$åÄ2z‘$çIô¿†„„İá†öÀãLÅú÷òòfÆ£§‰‘ÚEe‡ÔqP@¬¾Éç“Ø*4Q,D‹¹ãÿH¹œ  jş†PÏ¯Bs­âeõÒTxÉĞ·ÌBD±†ùàÍ¸2nK± ¯pêOæ>MºóöÕª71Ê¾7I:1"òØK Hbîód1ÊÙ¶¶°ÉëG˜ZëCXv¼qlÓ«Lè4¹É:N›:ŞTèéW;V8b§.ĞgTçÔqÒÕ'}>Æq„e×KÆ§y@Ñ£BÿlÀ×:ëú»ÁãóšXS{}ÓQX|lÄÀCq,ÔŞ6TvúY’i—c•ìsMÎu§×î!R¢¶?ÍÜ-,E¾Sı«C{µY\”!kÜC¼ïhH_å|ÊF:sëÿ¼tÌ´ÏÌO{z^xĞûûh¯r´ñ¹ÉHÙ£<óÌ4gª4İ‘°_I"¿ü/ì«b‰¬³ï!sWfT«àtÆ!’5.H«›´”î1š#™vˆ—5ŒšL.ÉÖ†šÛ„q¬§N1Ün-„á5M`.¬å†'¡ ß££˜Ôİ¶fî>cšŸ/¡†á2‚‘ä`bk`µ3Æ¹çóîtKŒÚ(s‹öm-
(ƒÁæEÃf—³„ùµQÉcs´—ÌœÏé½“@Oãc‡Bq4Mfğ)İ^k¯¾ÍZÏwß-¦mÚKº9­TEĞRøF7„Ë’>:èˆbF…Ét´;7o‚»Â¢fæ¡bÅô wß)¦[­LW{Ü›ÂdIlg<€ãêÇ0 İ˜ø0~ù^å”µ{8_S
q#¥û~”J3`/¯Œ$„'^6†,–ëbKœŞÕ´„h¤şT†×À×Í]´d‚ó,£d¹çE‰^q“ôåæw‘|å|­X‚×s¬ˆ]­¸ğcªäº%¿Ï¼}#²ïºl1©õ1¼ç6uPµÉæKü9·Á-âcLg¢…%)œ90ğ~I'Î6Äñü‡t-â¢#	 »şÜÁÂÿÂút!éà0¿4¾™X¥ËiöÍÄ~„ôéEW×ŸjÓ=nñkÇÍ;ñı×¦eŒM½?Œª%Ë+šÔ’zÊ?ÄƒtšH½»ò@’ş¿ñÎ*!³Ÿ:6>7z6şõü*ƒNN<B TbúZ9nLy?¹m(y£ÊÈr˜aÈ¡¹xºqT}äbD®R$	òÄ>oÚóª;J³»e¾èÑ:	ùrZiñW+ØÎ¦¼6\óeërßí§ºH ²<(ÏÛÒ¥=ìÄqhô=æy[@/TÅ›öçGêK‰Æ‰èìšàÓé!üŞ3È=äsÑ¡b¯¶À—ÀØµ»ª²Ùi­¬tÍİ:Ó-¹Ëî#Òå]-%Ÿgƒ²˜¶@-ƒ ŒFdˆ”·Mƒ|Æ*[(*ï†h/ŒF7ò ˜J²*È…¶­Á‰!æ ÌçŠ rc¢±sƒO€İÙ‚ó '•PiS'‚> ¢U/ê	ªS&ûÊÅBR˜åa¸É²`n$¤Æ-SËLFLo’•d	MÕ5HÖ,r8Æ”!}•éA®{Ğ¸IÏÎÎª¾‘†(x‡ñZ¨¨ĞŠŒ?*·{Y»úßâ&¦†ğ’àÅŞo7Ë›^°¯[")6ÄÆ$ØW’Êƒ¿äÄŒg,¡ÍHN²#7°{î}ıŒ¤g¡š^aò“ç)‚ª»ÖºÑ0EgNï”~=òĞ«½ß–¦{üÜóĞMm¶Ãt×ÍšUÜ2¤},W£CH8IéŠk·ë ‘Iî¼«b? ü£iÃó#£3äÅ’9DìÓ[TàJ6¯£CãÑÉyùGö«×’Ÿê§Ñ€—ˆX¨_{E*GG@ê'²–/M#ùpM­>Ú²±¨15[RÛˆ¬à“ÇQÅ¿{y¼ÜLøêÂSÉÏ\ş+MÛJ¨´;È2óì¸]XĞ×NH—ˆß×^e’I¼°o~„ P±¸c€Î¢n6îZ"Ã­8ÜÜ~§Š-Šbrl‰›¼:+p˜6ÜHÒ#<Ò–œí¢.¾Ò²\9vH%l$ÚØ‰Ã„K¸@[Ò¨Îü¯…€"ÿˆ‚‘ó¸lˆ3.z†ô,‚ˆbz(Næ’Èn¢ğ$vJ!‹1hô¨Ó}'¿²_àF5$ à`œú[‚¢0 Õ.’´üYT-™ó[“;Kªn"0\ÌÄË$iM¸•äQ#€íÄ`ÆlAÕÑÖÙ©N`¬š½‚4ÿ|îªçyi"‡(e…ê
Ë—ù"P™s§–›¯Ğøi™dX¥_ ¡®T}ô“Œº5Úì¢Ÿ³DLGİtÙ¥˜Ë«CœúvRªÖdé«6Q~û8§è÷8ÑĞ¨J–Ú¤…|Ö-¹x-j¿]®±3Sæä.Dàà£(-¾+õIJ°oÌÿâğ„ß‹>—u‘Ùù^]£EçÉE5†Ÿ«öwş ©0tìá\[·vñÂÆzŸ|?<CC(UÉ–tÈı¼eƒ¢3Ôš5$4í“Ç‘¤dºqùş{½y‰•Rà—šá óW†¤¬”wqNqÛj’Ür'ÚªæM*{ŒãXU#=ƒ8Í>ŒŒí‹¾çÀØÍÔ‚ œÜÎo´Ô¹¤†û>#S;¾‰uƒÍxtˆy†={åãfİÙ«–è5!|.Va®«â>z‰=À÷ëª÷(Ô$!-šÉÍ3¿çCÎÁ)bÊıa¹ÖúçÛ/ëÎ#h4VQÊR«‹È1x°»å'ÚçïõØÂõ˜*ù4«ÀØ„êGg¿À(‹ (ç¯ÂõÔnù‰6"_N¢	HæEª5G};`ëõ~çd\MpvÅ²ø Sâ©Oï‘eĞ¹?ÉKU3Ó½±°ªã’
õÍÌ´a@6ØÛ]RŞJfbPé¦ĞYıiÍ¤îFÆ¹Ğé%3ò·çÊzŸRuBq–Y¢a°)²¹<g	ø}ÈÉEuRUjjOwO©¦ƒÒ-bÀ:ôLÔxmF}Wy³Ê09®€`¥ hö”Êlõî_†Ê‰}	¢‰âMFÈÊİÛKáÔÖöåîë·c3BâFNZŒrë²U´at
æÆ/¯-¨öèéYT)è%.V~œ´X f ñ¸¿uÿŠ
‡ÆŞÈ¥r‡i·ø÷±Í:rUŒbŠ?Ì–1*ÃOiSD1\ºOËé‰²û5‡“©+^p©3µašÏé}×ãt-¦™È×ÔÒªŠi„©Ç‹•:ã1Ó×9ìÈª(ŞˆèÍİ]$9±Ï½í†I]Šo?ïâßåºûš×6‰GdÓ»Ş2FÙèª÷¹‰‘ŒÑ~¡\F—àEÚ»®â×“3 ?¼êz’O‘@bŞq©¼ßóøn¤å¼Ö™‘£o;gxíÿîÂ„e%¯Õµù¼|çÛ=~|}uîUÈlU9ª¿NªÍJ±¡z»»¢‚Nü<Yıèœ³)µï.@E”àNTZ[tßãşRp¦Â‘Û×@gS'ïUE‰'Zñ¾¦küL±E<mÛ‹ê2i¢_×\B‹ÛijÅ°ı¯6$šj¥›ï–áúî4h;¾]ƒ!w¬¡@÷Õ_9˜q%&"ï›GûÅ‘€‰wÚÌëWW-åd†şõWöªaÑm('R*póD Ï}Œfl{§0¬“ë˜	ª‘‚ŸCÜÈOê•kœÿG‘·›á%X&Äe¼ }²ÄJMk~íz&8(.niäCµÂ7¿ÛTÛ'¯îaxğzÑzi‘ÅJ2âĞbàqfÄ;Œ€f2‘kTüx¨èk]ƒ
+¨8š‹At›Ö¡g_È"¡ªãÇIA¯ìş62@BxeŒëı¼ÆĞ”h*¿_81*³ÅJ%a0{éı¾Ü>'>¢m¹M­¡¨’°sğ½é -yÏì«ÂâØ€@ÌÑåDÓëö;Û“… ¨ó3üşô~£¯«-o „1Dı¹í$Tœ¡‡
v›šÉÆ}ìzÊĞmyT¥í²º+½6£CÈŞ­iúÉæè—‘+øÿƒ&dªT[miA:&…xA‹îıàî¼O0Sbıı[ßÆÇ•nßßgÍ×PşX@‰†S³¥›ìºŒ¨+¤i‘¶º"„ÈÓœÿŒÇÄ›‹ô±í´Vô@U¸Gğ^%!Š#‰¼->pp~)eV¸z%ëwZ\FÈÄäÂö³ø1.'Æ/Uuu&ÁÁ€¹Y·Æ Ì¯ü£J­6Q¾Nfp¯ä‹ãåÕ¨sª´zğ03³„×U2ùÂşÙ{_^ùğØš©´Qy5Ô®Aæ0PÕmJmÛrqå¥—ÕŸC`ò‡È¶ÉàºÊ
:¶I¾ÙÊx¹ É>m‚t¤ÉºÉıôk²î[…cl]ëw/Ügp®t°gÓ‰®BŒâä˜®:‹$sıO­|õŞ7‡7—Ü¥ƒ%F§k‘DCÄèk‚9İöG1Èî»õ1¸…˜¡¨ş4A)bÁ6ÿ\#Ú­şxÔéöNãÓ&Ô&ç;öÌîÕ›cLF¥ûò3B?,zÄSVGŞÙÃ	â’ë:ĞèÚ*úã`(0ÔŞi"’±ò®¶| ı ´ñ\ŞAM@cÓ»!<XÚ4ÆoFG1š±bòšî( £K˜¾CÅËêudÉ¥\j÷Ë·¯Ü‡‡µWŞ+K¹+l:bÄ‚]Ö&­ìış‡É’‹ß7òGª@õÖ&t ÂY‚Ô°ÖíKñ9vÔÏ±}iYFóøú–Ğ]$“¸?+V™Ê;Ì‚Âk@ ‰bK#Hˆ]ÆÌ<Bé(JĞk`Qm¿ å…4…QZ¢6¸5¸ÄòCåwg‘†b›¬bÂî~Èt‹|çş#Ÿ7O²}¬øåZ·k\È“årLNzËz£ÒcqáDo·ÇÊGÁµ^TaY:;8ç[ªX£>;O-[œÜà½·åám®ñ— N•ŸƒMŠmƒíÕ¤mö·Ç®W‰\y?%È‡«—^©œ¤“ddìmã\[lêF!BÜ¨üÑĞÖ#î¶x0¶ÙÌWım}á§V:ìôÃŞJJ¡¸MØàòÈa\¾Ã„|3~}[(XØÖÔqŠ¼iA$Hµ°%sÕ?v“ƒ Ù»ÏÑ¡PÉÊïóR"l«³õµ<½ÒÏ}”AmT=g½h®¾?Ã~V¹1èÄdR¯,3BTóB¢Ü7õˆãŸĞ2@-‰½óÑŞ¬?<Vˆa!GMØf`¢ ‹#jl	o;µMÄ È5¸ÒÂ5aM¡fæiDÙF,yçBj·±‚;4¼»QqMU•¤²ëøpÏhw{{=»ä™bÅs/œ.%`ÂĞnÜÏvLÔ¼sŸ|zïg"LWL•x'­1fØd Ÿ—AŒ›á$4_«I%Û¸Ù22{ñâm©ªÓÀ©(l°±rŞ*$1‰…o'És$^2¦q&
%Ö+.UÓİ(25¯ÚmKTkH?7ÙW—Mæx"YÀ+næ°ƒg¸wz/3©v´T«Ûz€~­»³…Çl<Ş,MàW±W>Ñ)Fö'¤ò»~lp<SõE–šC¾‰!uE¯…bzàÿRº1ÀËwè‰ÖêŸÀçYıxÔİ™Ğ¨4Ş_*ÜpCsˆÉ×óW¼pqµšKiO¶Ã63•EÕö­ta*0m0Îo»¡È…ÛVÒÑ*%¨ Íï<½ªñô+ÒÑ€Ş&‡Ã!æœLÅSá‘[g³‚l½¸ÀfBhU;S7Ró`I7R–)¶LDMëjló?Ìµ!V·;Q›ÇÛ-\õG´Ö¥Ø±~‰:ëc:7i«~Df-JÄC"…7´+Ípÿ‡p0Ñü+´ßXÛ_^Ä}Ì¡Ñ³ÍEöF¢rT‹zˆ?†Í”Æe#ˆË/–¬|^Q.s0ÕzlşœD~$Àg¤v{k!SIëº¹‡Ö¡QéKG/ş‚÷¶|§±S²^™W—óYãüFË¼g„@qÃÈ6¹À—Şu"Å%åäP‡qql™Fzpÿ™øÚ‘¸ÎãÒ@¼ôÍ¾ëŸó$çŞĞ:¢ı
*‰6+äwê ¨â•¨ı’™§A5““d¾¤Òa"»2\½ÛR+ãûMÖdFÖŒów=u‰İÎW/å¡¿†c9Ö€7¤’6ºgÛO°×wĞû3pÆÈíÉ¡ß@µµæÄlbÃj/«ç¦ã:OPY«Ôèq”bUôö(÷‘ò5¤ÓA;Ìw	.Î—¥9ò<|•İG°ßÉ:B}ô²Åà 8‘>‘1a{{
1û©a½öû5ƒ1™ÑÔ]ŸŞGĞ6¬Ép}£v<ú°=kÔ
h¶e.mc²u²ˆêĞÎ®?§¿¹Â&½½lw0âh‰Ï¸SµéºÆ:A%‘Ç«f{Æ‹$Ü¶[#>.xgl4K”±æaî6ÓÆ¥y¹smÑ…\€x[dZ«î3¶¦­#›Šü÷O–ÚtK$+(qû²¼?‡-Íá¶Kòõ±5è1@WÃZ;Şô`Z,¾'7Ù˜ñHÜ0E<T²ˆlóÁfª†§ãµÿ	àÇ%s]Ä/Çtà!Â6ıš—³6‘ş¢+~(gŠ.µdù¯-Àq‹Á*õ(uœ€q9=…3qÑÎT»ëy¨6d+
©»YÒT¢^8qpÂ94«§óùo¬I¬7}±Äo×QæóßN^­#(ß ¢œ3Œ¢N—¨‰>`áRŠÚùœZƒ3)NîG­ò¶óÎÛ½e´>¶”i–`MÅŸrãZ˜ÒL|àõ}Jø80Ğ•ıãCilÛİó İ9×>áü†.Zşğé»j™àŒÏ69FöŠtÊg¦Ô…°=€WCU_fA¯²¹,ÃC]„$±üuã|q¡\c-ÍiÕPvûùÜ\ó §B{\ÍÒ€Iå¡¸V¿÷­ó¹oŸ–ÙAkÏ_Ø	-İã³ÎÌÒš§S©ëÖ6A€ØÆh†â0+X~±ìaêC{ë˜Lh»I;Î¹qé>€(û1û[~¡\¦4S9y:g‡ \°òÏ{»’çïQˆ@„¡yĞÀ¼©áb¦êñ`` ú`Í›0ÆxÊˆ†¥Aµ*ëÑ
óošÛB±(Àñ)¦·º²³ÿ'ëxãøHfÒÒnn´*†ó6uA“ë_›hµËÑäró˜éÔÌCSóH‹ö<¬oj`º=ûş`lT÷İ J²q§2Ñ¼çÕÙç™=Cz`?(Bá2{è;b[ZÛ¼¨RëïÇËØ3İH>øéõ°.›
î°b0A¨
³–FêìpCİ·”Ç/#±Ú4¯j6Â´ìÚx‡Ö[DÆ~dˆ:½èñåºÚÒŒÚÏóÊ
ã™‹±C$È£ßÄÕ„X2²âÁæt
…Olÿâ-ŞFEc©—ù”T©"~¨i,TÉ~V0İ$Š³íPO8fÂ]ğı5 m•½k‘ânÅßkrÓ…àñ‘K¬ióƒ¤eØFLueÍchCÅ4€VÕiì/{Èl2¥O¢Yy;7
Ì–Ô ŞF^aœ-È:)gÇÉÒ­ôVê;SğÏĞ›Vû”DºŒñm.`¦¢ÙÑ8Ñ#käH'I]zÓÅŞfÃX<‹/@rQ§=Ë6¤dº®ˆdá›.vÃR° ²ç5f0ƒœp¸U Ÿûw¿Ùu¸ÿ¥ƒDB–qÀš1Î*Ú§ ğ*oFÕÉ<W§hcš[#b¿İ§ïõé¹”‚pRh;¤›9J¯t.‚Îde-+Vä+­Gº¡bŸ´àl÷Éµ…º–óÛ³=M"Ï‹^ÈíÉÄ:¿…Ø¯Ï:óöİ/èV<¶M¿Ú©jĞcK}ñY­tÉİ$¡†‘s‹d3»>ºF´ÑÑº[9ªZ•±®æìºıKãÔ”ï šï ¢²ààk*3q‰ 2Qdhj®ÀAt×ÛFœöQä‚=Aª¨%ÛÂM‹èkuA¬ã0F8¦Œ?]«¢]Á	.İü_ª`3Iº{î$	J\=íN]M¥ {$lmpApV„Áï'²ìÄ^à;jq/[éDZ'÷Œ¶È•šcƒÓB¤»ş®$©‡–/Å/UçvT{¶I&U½±÷?ˆïéÀ´Ê¶¶3(Ğ*RıktS‘R<:Æµô»ŒCb0Ïqÿ'ö#º÷Zi’w»ãÂPÏÉAá4æ°·Ä"‡€µ³“fsì-j¼ï`îÉÓ7a< ½µ±K´£†æfnê’]„í0ÆEqHsT×w2,-d|ŸÕó¼PöÔ$7Òwê×ÀµcIv£jƒ¦ç1™¬òcLÁ*l7 şøSlàØÌ ‹……I½wúMRËöú2t'bQÄ7¹¬½{‡	ßçaª6ådSìÉ#r5vÖ=iWe=ü}xZ~•YÃXã7÷õ‡ÃHÙŸ¯zNÂ.ÜñöPÒ¼%D2Ú$¢Ú ÉI.ÆŸ¸ÌQÈ©y7=;£Ô@.\³5…™œ§ûU]¢JöC1€×"ŒÀKÕ¡šY&&·„Ğÿ˜:Hœ×²(GµöH¹s¤T@İ¬…•š«™šf~¬¹^J9ó Ñ'ª	Š+^¦ óÕGŸ#õB®ZÄGvÍb™`eA(J³Ú‚‘\})d¹·Gú4nƒhÆÖª.e ä½È5®Æ7T©7à2:0¬ÕÑâ%ÑÊçMÖ×7wgØÎsÊ,æ¶æº@5~Â+†Y¥‘3x:dK›àº¿ÒØv©üÌ}"_Ñ{·C÷m` R;_÷Hñ.Ÿ\ŠË¯»hX>RÒ,ß½÷39(“¡ŒQ_½H3‘!éçãô·üÿ<ë}Å‘!#Ç´®.úLQó`K¨ÛCbvxSÛ;62Ó–ÎÎ™}z†½s~:Ö[{¶{61ú(cöî. %E.
ÜZGT<õu'$ÒL‚BÇúÿÌ`]KC.u~{ìRVŸ'4æ1*rS`^¹Ä¿6Ä°âÒÁÓïˆÅÏ®ZÍ¢ñØT¸2äÔw¦D+Œf//‡tQ/U@S´;ıpÄK¾-~F¦ÃS¶0n™r"CeıØö~6ÙÀÀ‡‡¡gP:E0³uß}l„İñõ×âLì}ÁBBc¢$}
|Ÿ¢n)‡,÷v´êKdéu7³W8’Ét¿Rµ.´bTx#è~rÈÑ¤Zñˆ©¹ÒHrqHo“†)wË¿R5_oˆ •GDÕİGAÄ˜Sù±ùş‰mçÁˆ™å¨£2J’¨©˜Øºõ@
/S„÷ğ0Ÿ,°ê5İVd`Œ/Ò®ËPM#¹Á”Ö’x4Ÿ/E±èØŠ‘`±d*é2K«‚ì|tµ’C£©3Ï- -ò†>Ò­xÃ‡sÆ,<p¡‚h1nî]€¢A#ë)RlU):«¿	ûò}jÆlÓÒù-µË9?ĞŠ+£M¥{$Âû%¢øË„Õïe±É­ÓÏ9éxµÜd1I®r~B‹Åp÷ŸÁ¾ßÜâ2¬B*á¯„÷E¿´Œ-<Öeç;}´£&é:	é¹€LŸ÷¤¨ÕÇãSiy»7a§i3¯r1Ÿê¢^ò¥-¦ôÌÕÆoUG}Äø#üªÈ/Âp	¶ää)\G½®!¥ùÂH~B ÕdVçÛ@Ûj‰› Å>‰l÷*®iÕÚM@-NWa$·ØoÂú¸Fµ÷EE@óÙWGtïaÜèÔmü8ûö˜·(”ZoŠ/éÓŸ,xtñ–¡§d	û\ÑFDY½(”Â'äA·¹D"+B÷¤§ğ*îb|Òg ßeñK®½V–Ç~uó&ìM%[è%•è·5.æWŠM?J§o@øËãíƒ§ÔxfÔ9kÂ~LıZ òV‚@X”AŠÍ|ÄKy?ßí¸Ò^(®‰J.”ùˆz€M Oˆb<8tO©Ï+¯cÜ0avıQĞ¶}í:ëqI-§óòBX›ı¤™	J¢Ÿ!(¼ú$0ÊçN[/$EŠ‘“ırL"ÔHnó!Ú‹,Ö¸0ùkÈçø‡£änÓØ!¤b½¨“ÌáS’¡¡³aò -¿*‡Öá¯Ac¦=m›\¼˜s	ée¸¸:Õj»–<ºÂ.A‹œCíù¦Aš5¼a.ªçİ+ÆFDg*-w'èQgwI{ôİÜ~'
-2ñö}¤.«Î2ÉUî·×Ma§ÀœòOMjUl?•™ç¶s*SğÇÙ§êQê^eÊmcÖ]ĞwÇ@_0¿«<uÒ*7—ÑkEBÂ´İ:ú–Œˆ÷Ä­D¥w½Í¡@œIÈd¹Wã—²æöWMŸ”İ0ã5Bv­óÜ©e›q$;ÄÏ‘z'øÆËñ‚=Õo€O1¿€‡i¡©2“íô²à·AOééóªr–—ÉX¤Dè`˜ë‰ù-BGÄzëCÄ&