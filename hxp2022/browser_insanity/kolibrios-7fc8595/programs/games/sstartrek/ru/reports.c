#include "sst.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

void attakreport(void) {
	if (future[FCDBAS] < 1e30) {
		proutn("�⠭�� �");/*Starbase in*/
		cramlc(1, batx, baty);
/* 		prout(" is currently under attack.");
		proutn("It can hold out until Stardate ");
 */		prout(" ��室���� ��� �⠪��.");
		proutn("��� �த�ন��� ���ᨬ� �� ");
		cramf(future[FCDBAS], 0,1);
		prout(".");
	}
	if (isatb == 1) {
		proutn("�⠭�� �");/*Starbase in*/
		cramlc(1, d.isx, d.isy);
/* 		prout(" is under Super-commander attack.");
		proutn("It can hold out until Stardate ");
 */		prout(" ��室���� ��� �⠪�� �㯥����������.");
		proutn("��� �த�ন��� ���ᨬ� �� ");
		cramf(future[FSCDBAS], 0, 1);
		prout(".");
	}
}
	

void report(int f) {
	char *s1,*s2,*s3;

	chew();
	s1 = (thawed?"��࠭����� ":"");/*thawed*/
	switch (length) {
		case 1: s2="�������/short"; break;
		case 2: s2="�।���/medium"; break;
		case 4: s2="�������/long"; break;
		default: s2="�������⭮� ���⥫쭮��/unknown length"; break;
	}
	switch (skill) {
		case SNOVICE: s3="����箪"; break;/*novice*/
		case SFAIR: s3="ᠫ���"; break;/*fair*/
		case SGOOD: s3="�⫨筨�"; break;/*good*/
		case SEXPERT: s3="��ᯥ��"; break;/*expert*/
		case SEMERITUS: s3="�������"; break;/*emeritus*/
		default: s3="�����"; break;/*skilled*/
	}
/* 	printf("\nYou %s playing a %s%s %s game.\n",
		   alldone? "were": "are now", s1, s2, s3);
 */	printf("\n�� %s a %s%s ���� �� ᫮����� %s.\n",
		   alldone? "��ࠫ�": "ᥩ�� ��ࠥ�", s1, s2, s3);
	if (skill>SGOOD && thawed && !alldone) prout("���� �⫨�� �� �뤠����.");/*No plaque is allowed*/
	/* if (tourn) printf("This is tournament game %d.\n", tourn); */
	if (tourn) printf("�� ��୨ୠ� ��� %d.\n", tourn);
	/* if (f) printf("Your secret password is \"%s\"\n",passwd); */
	if (f) printf("��� ᥪ��� ��஫� \"%s\"\n",passwd);
	/* printf("%d of %d Klingon ships have been destroyed", */
	printf("%d �� %d �������᪨� ��ࠡ��� 㭨�⮦���",
		   d.killk+d.killc+d.nsckill, inkling);
	/* if (d.killc) printf(", including %d Commander%s.\n", d.killc, d.killc==1?"":"s"); */
	if (d.killc) printf(", ������ %d ���������%s.\n", d.killc, d.killc==1?"�":"��");
	else if (d.killk+d.nsckill > 0) prout(", �� �� ������ ���������.");/*but no Commanders*/
	else prout(".");
/* 	if (skill > SFAIR) printf("The Super Commander has %sbeen destroyed.\n",
						  d.nscrem?"not ":"");
 */	if (skill > SFAIR) printf("�㯥���������� %s�� 㭨�⮦��.\n",
						  d.nscrem?"�� ":"");
	if (d.rembase != inbase) {
/* 		proutn("There ");
		if (inbase-d.rembase==1) proutn("has been 1 base");
		else {
			proutn("have been ");
			crami(inbase-d.rembase, 1);
			proutn(" bases");
		}
		proutn(" destroyed, ");
		crami(d.rembase, 1);
		prout(" remaining.");
 */		
		if (inbase-d.rembase==1) proutn("�����⢥���� �⠭�� �뫠 㭨�⮦���,");
		else {
			proutn("�뫮 ");
			crami(inbase-d.rembase, 1);
			proutn(" �⠭権 㭨�⮦���, ");
		}
		crami(d.rembase, 1);
		prout(" ��⠫���.");
	}
	else printf("�ᥣ� %d �⠭権.\n", inbase);/*There are %d bases*/
	if (REPORTS || iseenit) {
		/* Don't report this if not seen and
			either the radio is dead or not at base! */
		attakreport();
		iseenit = 1;
	}
/* 	if (casual) printf("%d casualt%s suffered so far.\n",
					   casual, casual==1? "y" : "ies");
 */	if (casual) printf("%d ᬥ��%s �।� �������.\n",
					   casual, casual==1? "�" : "��");
#ifdef CAPTURE
/*     if (brigcapacity != brigfree) printf("%d Klingon%s in brig.\n",
    							brigcapacity-brigfree, brigcapacity-brigfree>1 ? "s" : "");
 */    if (brigcapacity != brigfree) printf("%d �������%s �� �ਣ�.\n",
    							brigcapacity-brigfree, brigcapacity-brigfree>1 ? "��" : "");
/*     if (kcaptured > 0) printf("%d captured Klingon%s turned in to Star Fleet.\n", 
                               kcaptured, kcaptured>1 ? "s" : "");
 */    if (kcaptured > 0) printf("%d ������� �������%s ��ᮥ�������� � ��������� �����.\n", 
                               kcaptured, kcaptured>1 ? "��" : "");
#endif
/* 	if (nhelp) printf("There were %d call%s for help.\n",
					  nhelp, nhelp==1 ? "" : "s");
 */	if (nhelp) printf("��䨪�஢��� %d �맮�%s � �����.\n",
					  nhelp, nhelp==1 ? "" : "��");
	if (ship == IHE) {
		proutn("� ��� ��⠫��� ");/**/
		if (nprobes) crami(nprobes,1);
		else proutn("0");/*no*/
		proutn(" ࠧ�������");/*deep space probe*/
		if (nprobes!=1) proutn("��");/*s*/
		prout(".");
	}
	if (REPORTS && future[FDSPROB] != 1e30) {
		if (isarmed) 
			/* proutn("An armed deep space probe is in"); */
			proutn("������뢠⥫�� ���� � ����������� � �窥");
		else
			proutn("������뢠⥫�� ���� � �窥");/*A deep space probe is in*/
		cramlc(1, probecx, probecy);
		prout(".");
	}
	if (icrystl) {
		if (cryprob <= .05)
			/* prout("Dilithium crystals aboard ship...not yet used."); */
			prout("����⨥�� ���⠫�� �� �����...�� �뫨 �ᯮ�짮����.");
		else {
			int i=0;
			double ai = 0.05;
			while (cryprob > ai) {
				ai *= 2.0;
				i++;
			}
/* 			printf("Dilithium crystals have been used %d time%s.\n",
				   i, i==1? "" : "s");
 */			printf("����⨥�� ���⠫� �ᯮ�짮������ %d ࠧ%s.\n",
				   i, (i>1 && i<5)? "�" : "");
		}
	}
	skip(1);
}
	
void lrscan(void) {
	int x, y;
	chew();
	if (damage[DLRSENS] != 0.0) {
		/* Now allow base's sensors if docked */
		if (condit != IHDOCKED) {
			/* prout("LONG-RANGE SENSORS DAMAGED."); */
			prout("������� �������� ������ ����������.");
			return;
		}
		skip(1);
		/* proutn("Starbase's long-range scan for"); */
		proutn("�ᯮ��㥬 ᥭ��� �⠭樨 ���");
	}
	else {
		skip(1);
		/* proutn("Long-range scan for"); */
		proutn("�ந������ ���쭥� ᪠��஢���� ���");
	}
	cramlc(1, quadx, quady);
	skip(1);
	if (coordfixed)
	for (y = quady+1; y >= quady-1; y--) {
		for (x = quadx-1; x <= quadx+1; x++) {
			if (x == 0 || x > 8 || y == 0 || y > 8)
				printf("   -1");
			else {
				printf("%5d", d.galaxy[x][y]);
				// If radio works, mark star chart so
				// it will show current information.
				// Otherwise mark with current
				// value which is fixed. 
				starch[x][y] = damage[DRADIO] > 0 ? d.galaxy[x][y]+1000 :1;
			}
		}
		putchar('\n');
	}
	else
	for (x = quadx-1; x <= quadx+1; x++) {
		for (y = quady-1; y <= quady+1; y++) {
			if (x == 0 || x > 8 || y == 0 || y > 8)
				printf("   -1");
			else {
				printf("%5d", d.galaxy[x][y]);
				// If radio works, mark star chart so
				// it will show current information.
				// Otherwise mark with current
				// value which is fixed. 
				starch[x][y] = damage[DRADIO] > 0 ? d.galaxy[x][y]+1000 :1;
			}
		}
		putchar('\n');
	}

}

void dreprt(void) {
	int jdam = FALSE, i;
	chew();

	for (i = 1; i <= ndevice; i++) {
		if (damage[i] > 0.0) {
			if (!jdam) {
				skip(1);
/* 				prout("DEVICE            -REPAIR TIMES-");
				prout("                IN FLIGHT   DOCKED");
 */				prout("����������        -����� �� ������-");
				prout("                � �������   �� �������");
				jdam = TRUE;
			}
			printf("  %16s ", device[i]);
			cramf(damage[i]+0.05, 8, 2);
			proutn("  ");
			cramf(docfac*damage[i]+0.005, 8, 2);
			skip(1);
		}
	}
	/* if (!jdam) prout("All devices functional."); */
	if (!jdam) prout("�� �����⥬� ��ࠢ��.");
}

void chart(int nn) {
	int i,j;

	chew();
	skip(1);
	if (stdamtim != 1e30 && stdamtim != d.date && condit == IHDOCKED) {
/* 		prout("Spock-  \"I revised the Star Chart from the");
		prout("  starbase's records.\"");
 */		prout("����-  \"� ������� �������� �����");
		prout("  �� ����� �⠭樨.\"");
		skip(1);
	}
	/* if (nn == 0) prout("STAR CHART FOR THE KNOWN GALAXY"); */
	if (nn == 0) prout("�������� ����� ��������� ����� ���������");
	if (stdamtim != 1e30) {
		if (condit == IHDOCKED) {
			/* We are docked, so restore chart from base information -- these values won't update! */
			stdamtim = d.date;
			for (i=1; i <= 8 ; i++)
				for (j=1; j <= 8; j++)
					if (starch[i][j] == 1) starch[i][j] = d.galaxy[i][j]+1000;
		}
		else {
			proutn("(��᫥���� ���������� ������ ");/*Last surveillance update*/
			cramf(d.date-stdamtim, 0, 1);
			prout(" �������� ��� �����.)");/*stardates ago*/
		}
	}
	if (nn ==0) skip(1);

	prout("      1    2    3    4    5    6    7    8");
	prout("    ----------------------------------------");
	if (nn==0) prout("  -");
	if (coordfixed)
	for (j = 8; j >= 1; j--) {
		printf("%d -", j);
		for (i = 1; i <= 8; i++) {
			if (starch[i][j] < 0) // We know only about the bases
				printf("  .1.");
			else if (starch[i][j] == 0) // Unknown
				printf("  ...");
			else if (starch[i][j] > 999) // Memorized value
				printf("%5d", starch[i][j]-1000);
			else
				printf("%5d", d.galaxy[i][j]); // What is actually there (happens when value is 1)
		}
		prout("  -");
	}
	else
	for (i = 1; i <= 8; i++) {
		printf("%d -", i);
		for (j = 1; j <= 8; j++) {
			if (starch[i][j] < 0) // We know only about the bases
				printf("  .1.");
			else if (starch[i][j] == 0) // Unknown
				printf("  ...");
			else if (starch[i][j] > 999) // Memorized value
				printf("%5d", starch[i][j]-1000);
			else
				printf("%5d", d.galaxy[i][j]); // What is actually there (happens when value is 1)
		}
		prout("  -");
	}
	if (nn == 0) {
		skip(1);
		crmshp();
		proutn(" ��室���� � �窥");/*is currently in*/
		cramlc(1, quadx, quady);
		skip(1);
	}
}
		
		
void srscan(int l) {
	static char requests[][3] =
		{"","da","co","po","ls","wa","en","to","sh","kl","ti"};
	char *cp;
	int leftside=TRUE, rightside=TRUE, i, j, jj, k=0, nn=FALSE;
	int goodScan=TRUE;
	switch (l) {
		case 1: // SRSCAN
			if (damage[DSRSENS] != 0) {
				/* Allow base's sensors if docked */
				if (condit != IHDOCKED) {
					/* prout("SHORT-RANGE SENSORS DAMAGED"); */
					prout("������� ������� ����������");
					goodScan=FALSE;
				}
				else
					/* prout("[Using starbase's sensors]"); */
					prout("[�ᯮ��㥬 ᥭ��� �⠭樨]");
			}
			if (goodScan)
				starch[quadx][quady] = damage[DRADIO]>0.0 ?
									   d.galaxy[quadx][quady]+1000:1;
			scan();
			if (isit("chart")) nn = TRUE;
			if (isit("no")) rightside = FALSE;
			chew();
			prout("\n    1 2 3 4 5 6 7 8 9 10");
			break;
		case 2: // REQUEST
			while (scan() == IHEOL)
				/* printf("Information desired? "); */
				printf("�������� ���ଠ��? ");
			chew();
			for (k = 1; k <= 10; k++)
				if (strncmp(citem,requests[k],min(2,strlen(citem)))==0)
					break;
			if (k > 10) {
/* 				prout("UNRECOGNIZED REQUEST. Legal requests are:\n"
					 "  date, condition, position, lsupport, warpfactor,\n"
					 "  energy, torpedoes, shields, klingons, time.");
 */				prout("������ �����������. ���४�� ������ (��� �㪢�):\n"
					 "  date(���), condition(���ﭨ�), position(���������),\n"
					 "  lsupport (��������ᯥ祭��), warpfactor (���-䠪��),\n"
					 "  energy(���ࣨ�), torpedoes(�௥��), shields (ᨫ��� ���),\n"
					 "  klingons(��������), time(�६�).");
				return;
			}
			// no "break"
		case 3: // STATUS
			chew();
			leftside = FALSE;
			skip(1);
	}
	for (i = 1; i <= 10; i++) {
		int jj = (k!=0 ? k : i);
		if (leftside) {
			if (coordfixed) {
				printf("%2d  ", 11-i);
				for (j = 1; j <= 10; j++) {
					if (goodScan || (abs((11-i)-secty)<= 1 && abs(j-sectx) <= 1))
						printf("%c ",quad[j][11-i]);
					else
						printf("- ");
				}
			} else {
				printf("%2d  ", i);
				for (j = 1; j <= 10; j++) {
					if (goodScan || (abs(i-sectx)<= 1 && abs(j-secty) <= 1))
						printf("%c ",quad[i][j]);
					else
						printf("- ");
				}
			}
		}
		if (rightside) {
			switch (jj) {
				case 1:
					printf(" �������� ���      %.1f", d.date);/*Stardate*/
					break;
				case 2:
					if (condit != IHDOCKED) newcnd();
					switch (condit) {
						case IHRED: cp = "�������"; break;/*RED*/
						case IHGREEN: cp = "�������"; break;/*GREEN*/
						case IHYELLOW: cp = "������"; break;/*YELLOW*/
						case IHDOCKED: cp = "�����������"; break;/*DOCKED*/
					}
					/* printf(" Condition     %s", cp); */
					printf(" ����ﭨ�/����� %s", cp);
#ifdef CLOAKING
				    if (iscloaked) printf(", ���������");/*CLOAKED*/
#endif
					break;
				case 3:
					printf(" ���������     ");/*Position*/
					cramlc(0, quadx, quady);
					putchar(',');
					cramlc(0, sectx, secty);
					break;
				case 4:
					printf(" ��������ᯥ祭��  ");/*Life Support*/
					if (damage[DLIFSUP] != 0.0) {
						if (condit == IHDOCKED)
/* 							printf("DAMAGED, supported by starbase");
						else
							printf("DAMAGED, reserves=%4.2f", lsupres);
 */							printf("����������, ��⠥��� �� �⠭樨");
						else
							printf("����������, १��=%4.2f", lsupres);
					}
					else
						printf("�������");/*ACTIVE*/
					break;
				case 5:
					printf(" ���-䠪��   %.1f", warpfac);/*Warp Factor*/
					break;
				case 6:
					printf(" ���ࣨ�       %.2f", energy);/*Energy */
					break;
				case 7:
					printf(" ��௥�        %d", torps);/*Torpedoes*/
					break;
				case 8:
					printf(" ������ ���       ");/*Shields*/
					if (damage[DSHIELD] != 0)
						printf("����������,");/*DAMAGED*/
					else if (shldup)
						printf("�������,");/*UP*/
					else
						printf("���������,");/*DOWN*/
					printf(" %d%% %.1f ������",/*units*/
						   (int)((100.0*shield)/inshld + 0.5), shield);
					break;
				case 9:
					printf(" ��������� ��⠫��� %d", d.remkl);/*Klingons Left*/
					break;
				case 10:
					printf(" �६��� ��⠫���     %.2f", d.remtime);/*Time Left*/
					break;
			}
					
		}
		skip(1);
		if (k!=0) return;
	}
	if (nn) chart(1);
}
			
			
void eta(void) {
	int key, ix1, ix2, iy1, iy2, prompt=FALSE;
	int wfl;
	double ttime, twarp, tpower;
	if (damage[DCOMPTR] != 0.0) {
		/* prout("COMPUTER DAMAGED, USE A POCKET CALCULATOR."); */
		prout("��������� ���������, ��������� ���������� �����������.");
		skip(1);
		return;
	}
	if (scan() != IHREAL) {
		prompt = TRUE;
		chew();
		/* proutn("Destination quadrant and/or sector? "); */
		proutn("����࠭� �����祭�� �/��� ᥪ��? ");
		if (scan()!=IHREAL) {
			huh();
			return;
		}
	}
	iy1 = aaitem +0.5;
	if (scan() != IHREAL) {
		huh();
		return;
	}
	ix1 = aaitem + 0.5;
	if (scan() == IHREAL) {
		iy2 = aaitem + 0.5;
		if (scan() != IHREAL) {
			huh();
			return;
		}
		ix2 = aaitem + 0.5;
	}
	else {	// same quadrant
		ix2 = ix1;
		iy2 = iy1;
		ix1 = quady;	// ya got me why x and y are reversed!
		iy1 = quadx;
	}

	if (ix1 > 8 || ix1 < 1 || iy1 > 8 || iy1 < 1 ||
		ix2 > 10 || ix2 < 1 || iy2 > 10 || iy2 < 1) {
		huh();
		return;
	}
	dist = sqrt(square(iy1-quadx+0.1*(iy2-sectx))+
				square(ix1-quady+0.1*(ix2-secty)));
	wfl = FALSE;

	/* if (prompt) prout("Answer \"no\" if you don't know the value:"); */
	if (prompt) prout("�⢥��� \"no\" �᫨ �� �� ����� ���祭��:");
	while (TRUE) {
		chew();
		/* proutn("Time or arrival date? "); */
		proutn("�६� ��� ��� �ਡ���? ");
		if (scan()==IHREAL) {
			ttime = aaitem;
			if (ttime > d.date) ttime -= d.date; // Actually a star date
			if (ttime <= 1e-10 ||
				(twarp=(floor(sqrt((10.0*dist)/ttime)*10.0)+1.0)/10.0) > 10) {
				/* prout("We'll never make it, sir."); */
				prout("�� ������� �� ᤥ���� ��, ���.");
				chew();
				return;
			}
			if (twarp < 1.0) twarp = 1.0;
			break;
		}
		chew();
		proutn("���-䠪��? ");/*Warp factor*/
		if (scan()== IHREAL) {
			wfl = TRUE;
			twarp = aaitem;
			if (twarp<1.0 || twarp > 10.0) {
				huh();
				return;
			}
			break;
		}
		/* prout("Captain, certainly you can give me one of these."); */
		prout("����⠭, ��� ��।������ �㦭� ����� ���� �� ��ਠ�⮢.");
	}
	while (TRUE) {
		chew();
		ttime = (10.0*dist)/square(twarp);
		tpower = dist*twarp*twarp*twarp*(shldup+1);
		if (tpower >= energy) { // Suggestion from Ethan Staffin -- give amount needed
			/* prout("Insufficient energy, sir: we would need "); */
			prout("�������筮 ���ࣨ�, ���: ��� �㦭� ");
			cramf(tpower, 1, 1);
			proutn (" ������.");/*units*/
			if (shldup==0 || tpower > energy*2.0) {
				if (!wfl) return;
				/* proutn("New warp factor to try? "); */
				proutn("�஡㥬 ��㣮� ���-䠪��? ");
				if (scan() == IHREAL) {
					wfl = TRUE;
					twarp = aaitem;
					if (twarp<1.0 || twarp > 10.0) {
						huh();
						return;
					}
					continue;
				}
				else {
					chew();
					skip(1);
					return;
				}
			}
/* 			prout("But if you lower your shields,");
			proutn("remaining");
 */			prout("�� �᫨ ������� ᨫ��� ���,");
			proutn("��⠭����");
			tpower /= 2;
		}
		else
			proutn("��⠭����"); /*Remaining*/
		proutn(" ���ࣨ� ");/*energy will be*/
		cramf(energy-tpower, 1, 1);
		prout(".");
		if (wfl) {
			/* proutn("And we will arrive at stardate "); */
			proutn("� �� �ਫ�⨬ � �㦭�� ��� � ��� ");
			cramf(d.date+ttime, 1, 1);
			prout(".");
		}
		else if (twarp==1.0)
			/* prout("Any warp speed is adequate."); */
			prout("��� ���ந� �� ᪮���� ��௠.");
		else {
			/* proutn("Minimum warp needed is "); */
			proutn("�������쭮 �ॡ㥬�� ���-᪮���� ");
			cramf(twarp, 1, 2);
			skip(1);
			/* proutn("and we will arrive at stardate "); */
			proutn("� �� �ਫ�⨬ � �㦭�� ��� � ��� ");
			cramf(d.date+ttime, 1, 2);
			prout(".");
		}
		if (d.remtime < ttime)
			/* prout("Unfortunately, the Federation will be destroyed by then."); */
			prout("��砫쭮, �� � ⮬� �६��� ������� �㤥� 㭨�⮦���.");
		if (twarp > 6.0)
			/* prout("You'll be taking risks at that speed, Captain"); */
			prout("�� ������ �������� �᪨ ⠪�� ᪮���, ����⠭");
		if ((isatb==1 && d.isy == ix1 && d.isx == iy1 &&
			 future[FSCDBAS]< ttime+d.date)||
			(future[FCDBAS]<ttime+d.date && baty==ix1 && batx == iy1))
			/* prout("The starbase there will be destroyed by then."); */
			prout("�⠭�� �㤥� 㦥 㭨�⮦��� � �⮬� �६���.");
		/* proutn("New warp factor to try? "); */
		proutn("�஡㥬 ��㣮� ���-䠪��? ");
		if (scan() == IHREAL) {
			wfl = TRUE;
			twarp = aaitem;
			if (twarp<1.0 || twarp > 10.0) {
				huh();
				return;
			}
		}
		else {
			chew();
			skip(1);
			return;
		}
	}
			
}
