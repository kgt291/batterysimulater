#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <stdlib.h>
#include <cmath>
#include <vector>
using namespace std;

float cu[4] = { 0.0 };
float cuv[100][4] = { 0.0 };
float tv[100][4] = { 0.0 };

void startkrr(int a, int k) {
	for (int i = 0; i < a; i++) {
		FILE *fp = NULL;
		errno_t err;
		if (i == 0) err = fopen_s(&fp, "dualfoil1.txt", "w");
		else if (i == 1) err = fopen_s(&fp, "dualfoil2.txt", "w");
		else if (i == 2) err = fopen_s(&fp, "dualfoil3.txt", "w");
		else if (i == 3) err = fopen_s(&fp, "dualfoil4.txt", "w");
		if (err != 0) cout << "파일 오픈 실패" << endl;
		fputs("50        ! lim,   limit on number of iterations\n", fp);
		fputs("100.0d-06 ! h1,  thickness of negative electrode (m)\n", fp);
		fputs("25.d-06   ! h2,  thickness of separator (m)\n", fp);
		fputs("100.0d-06 ! h3,  thickness of positive electrode (m)\n", fp);
		fputs("25.d-06   ! hcn, thickness of negative current collector (m)\n", fp);
		fputs("25.d-06   ! hcp, thickness of positive current collector (m)\n", fp);
		fputs("80        ! n1,    number of nodes in negative electrode(set=0 if in foil mode)\n", fp);
		fputs("40        ! n2,    number of nodes in separator\n", fp);
		fputs("80        ! n3,    number of nodes in positive electrode\n", fp);
		fputs("100       ! n4, number of nodes in solid particle\n", fp);
		fputs("0	    ! mvdc1, flag for variable solid diff coeff in anode\n", fp);
		fputs("0         ! mvdc3, flag for variable solid diff coeff in cathode\n", fp);
		fputs("20	    ! lims, number of iterations for solid phase convergence\n", fp);
		fputs("298.d0    ! T      temperature (K)\n", fp);
		fputs("1000.0    ! xi(1,1), initial salt concentration (mol/m3), 1200 needed for constant load short circuit\n", fp);
		fputs("0.6      ! x,     initial stoichiometric parameter for neg. (ignored if n1=0) 0.67\n", fp);
		fputs("0.5       ! y,     initial stoichiometric parameter for positive based on formula unit where 0<y<1\n", fp);
		fputs("30.0d0    ! tmmax, maximum time step size (s)\n", fp);
		fputs("3.9d-14   ! dfs1,  (ignored in Foil mode) diffusion coef. in negative solid (m2/s) 0.58d-14,\n", fp);
		fputs("1.0d-13   ! dfs3,  diffusion coef. in positive solid (m2/s) 0.8d-14, 3.d-14\n", fp);
		fputs("10.0d-6   ! Rad1,  radius of negative particles (m) (ignored in Foil mode) 0.0000042, 0.0000078\n", fp);
		fputs("10.0d-6   ! Rad3,  radius of positive particles (m) 0.000002, 17\n", fp);
		fputs("0.3       ! ep1,   volume fraction of electrolyte in negative electrode\n", fp);
		fputs("0.0d0     ! epp1,  volume fraction of polymer in negative electrode\n", fp);
		fputs("0.1       ! epf1,  volume fraction of inert filler in negative electrode\n", fp);
		fputs("0.0d0     ! epg1,  volume fraction of gas in negative\n", fp);
		fputs("1.0       ! ep2,   ep2+epp2=1.0  volume fraction of electrolyte in separator\n", fp);
		fputs("0.0d0     ! epp2,  volume fraction of polymer in separator\n", fp);
		fputs("0.0d0     ! epg2,  volume fraction gas in separator\n", fp);
		fputs("0.3       ! ep3,   volume fraction of electrolyte in positive electrode\n", fp);
		fputs("0.0d0     ! epp3,  volume fraction of polymer in positive electrode\n", fp);
		fputs("0.2       ! epf3,  volume fraction of inert filler in positive electrode\n", fp);
		fputs("0.0d0     ! epg3,  volume fraction of gas in positive\n", fp);
		fputs("100.0d0   ! sig1,  conductivity of negative matrix (S/m) (ignored in Foil mode) 124.28\n", fp);
		fputs("10.0d0    ! sig3,  conductivity of positive matrix (S/m) 23.43\n", fp);
		fputs("1.0d-5    ! rka1,  rate constant for negative reaction 2d-9\n", fp);
		fputs("3.d-11    ! rka3,  rate constant for positive reaction, changed from 3 to 4 4d-9\n", fp);
		fputs("0.001d0   ! ranode, anode film resistance (ohm-m2) 0.88d-2\n", fp);
		fputs("0.000d0   ! rcathde,  cathode film resistance (ohm-m2) 2.0d-2 1.0d-2, 1.2d-2\n", fp);
		fputs("372.d0    ! cot1,  coulombic capacity of negative material (mAh/g) \n", fp);
		fputs("274.d0    ! cot3,  coulombic capacity of positive material (mAh/g)\n", fp);
		fputs("1324.0    ! re,    density of electrolyte (kg/m3)\n", fp);
		fputs("1800.0    ! rs1,   density of negative insertion material (kg/m3)\n", fp);
		fputs("5010.0    ! rs3,   density of positive insertion material (kg/m3)\n", fp);
		fputs("1800.0    ! rf,    density of inert filler (kg/m3)\n", fp);
		fputs("1780.0    ! rpl,   (not used here) density of polymer material (kg/m3)\n", fp);
		fputs("0.0d0     ! rc,    density of inert separator material (kg/m3)\n", fp);
		fputs("8954.0    ! rcn,   density of negative current collector (kg/m3) [copper foil]\n", fp);
		fputs("2707.0    ! rcp,   density of positive current collector (kg/m3) [aluminum foil]\n", fp);
		fputs("0.0d0     ! htc,   heat-transfer coefficient at ends of cell stack (W/m2K) 0.36\n", fp);
		fputs("2000.0d0  ! Cp,    heat capacity of system (J/kg-K) 1200\n", fp);
		fputs("298.d0    ! Tam,   ambient air temperature (K)\n", fp);
		fputs("1         ! ncell, number of cells in a cell stack\n", fp);
		fputs("2         ! lht,   0 uses htc,  1 calcs htc,  2 isothermal\n", fp);
		fputs("1         ! il1,   1 for long print-out  0 for short print-out\n", fp);
		fputs("10        ! il2,   prints every il2 th node in long print-out\n", fp);
		fputs("10        ! il3,   prints every il3 th time step in long print-out\n", fp);
		fputs("1         ! lflag, 0 for electrolyte in separator only, 1 for uniform\n", fp);
		fputs("0         ! imp,   0 for no impedance, 1 for impedance\n", fp);
		fputs("0.0d0     ! capp1, capacitance of negative material (F/m2)\n", fp);
		fputs("0.0d0     ! capp3, capacitance of positive material (F/m2)\n", fp);
		fputs("0         ! lpow   0 for no power peaks, 1 for power peaks\n", fp);
		fputs("0         ! jsol   calculate solid profiles if 1 < jsol < nj\n", fp);
		fputs("0         ! nside  flag to turn on (1) or off (0) side reactions\n", fp);
		fputs("0.0d0     ! rksa1   rate constant side reaction 1 negative (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksc1   rate constant side reaction 1 positive (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksa2   rate constant side reaction 2 negative (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksc2   rate constant side reaction 2 positive (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksa3   rate constant side reaction 3 negative (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksc3   rate constant side reaction 3 positive (ignored if nside=0)\n", fp);
		fputs("3         ! nneg   see below\n", fp);
		fputs("11        ! nprop  see below\n", fp);
		fputs("6        ! npos   see below\n", fp);
		fputs("1         ! lcurs, number of current changes\n", fp);
		float cuu;
		if (i == 0) cuu = cu[0];
		else if (i == 1) cuu = cu[1];
		else if (i == 2) cuu = cu[2];
		else if (i == 3) cuu = cu[3];
		char mybuff[50];
		sprintf_s(mybuff, sizeof(mybuff), "%.2fd0  5.0d0  1  2.0d0  4.4d0\n", cuu);
		fputs(mybuff, fp);
		fputs("\n\n\n", fp);
		fputs("	EXPLANATIONS\n", fp);
		fputs("lines 20-22: ep1, epp1, and epf1\n", fp);
		fputs("	Set equal to 0.0 when running in Foil mode (metn = 1)\n\n", fp);
		fputs("line 50: il1", fp);
		fputs("          1 gives long print-out no matter if a run converges or not\n", fp);
		fputs("		   The long print-out stops at t(noncovergence).\n", fp);
		fputs("          0 gives short print-out if a run converges but a long\n", fp);
		fputs("            print-out if the run does not converge.\n\n", fp);
		fputs("line 59: lcurs,  number of current changes\n\n", fp);
		fputs("line 60 onward:  cu(i), tt(i), mc(i), vcutlo(i), vcuthi(i)\n", fp);
		fputs("     cu(i) The ith value of the current (A/m2), potential (V), power (W/m2)\n", fp);
		fputs("           or load (Ohm-m2) of the segment\n", fp);
		fputs("     tt(i) The ith value of the time (min) or cutoff potential (V)\n", fp);
		fputs("           of the segment\n", fp);
		fputs("     mc(i) The mode of the segment; 0 for potentiostatic, 1 for galvanostatic\n", fp);
		fputs("	   for a given time, 2 for galvanostatic to a cutoff potential,\n", fp);
		fputs("	   -1 for galvanostatic for a given time with a tapered current upon\n", fp);
		fputs("	   reaching a cutoff potential, -2 for specified power (in W/m2), and\n", fp);
		fputs("         -3 for specified load (in ohm-m2)\n", fp);
		fputs("	 vcutlo(i) low voltage cutoff for current step\n", fp);
		fputs("	 vcuthi(i) high voltage cutoff for current step\n\n", fp);
		fputs("nneg:\n", fp);
		fputs("    1 ! Li foil\n", fp);
		fputs("    2 ! Carbon (petroleum coke)\n", fp);
		fputs("    3 ! MCMB 2528 graphite (Bellcore) (0.01 < x < 0.90)\n", fp);
		fputs("    4 ! TiS2\n", fp);
		fputs("    5 ! Tungsten oxide (LixWO3 with 0<x<0.67)\n", fp);
		fputs("    6 ! Lonza KS6 graphite (Bellcore)\n", fp);
		fputs("    7 ! Albertus MH\n", fp);
		fputs("    8 ! Add your own negative electrode\n\n", fp);
		fputs("nprop:    1 ! AsF6 in methyl acetate\n", fp);
		fputs("    2 ! Perchlorate in PEO\n", fp);
		fputs("    3 ! Sodium Triflate in PEO\n", fp);
		fputs("    4 ! LiPF6 in PC (Sony cell simulation)\n", fp);
		fputs("    5 ! Perchlorate in PC (West simulation)\n", fp);
		fputs("    6 ! Triflate in PEO\n", fp);
		fputs("    7 ! LiPF6 in EC/DMC and p(VdF-HFP) (Bellcore)\n", fp);
		fputs("    8 ! LiPF6 in EC/DMC and p(VdF-HFP) (Bellcore) cell #2\n", fp);
		fputs("    9 ! Ideal ion exchange membrane\n", fp);
		fputs("   10 ! TFSI in PEMO at 40 C (oxymethylene-linked PEO) (LBL)\n", fp);
		fputs("   11 ! LiPF6 in EC:DMC (liquid)\n", fp);
		fputs("   12 ! LiTFSI in PEO at 85 C (LBL)\n", fp);
		fputs("   13 ! Paxton 30% KOH in H2O\n", fp);
		fputs("   14 ! Add your own electrolyte\n\n", fp);
		fputs("npos:\n", fp);
		fputs("    1 ! TiS2\n", fp);
		fputs("    2 ! Spinel Mn2O4 (lower plateau)\n", fp);
		fputs("    3 ! NaCoO2:  Sodium cobalt oxide (P2 phase, 0.3<y<0.92)\n", fp);
		fputs("    4 ! Spinel Mn2O4 (upper plateau) (0.2 < y < 1.0)\n", fp);
		fputs("    5 ! Tungsten oxide (LixWO3 with 0<x<0.67)\n", fp);
		fputs("    6 ! CoO2 (Cobalt dioxide) (0.5 < y < 0.99)\n", fp);
		fputs("    7 ! V2O5 (Vanadium oxide) (0 < y < 0.95)\n", fp);
		fputs("    8 ! Ni0.8Co0.2O2 (Gen 1) (0.4 < y < 0.99)\n", fp);
		fputs("    9 ! Spinel Mn2O4 (Bellcore)\n", fp);
		fputs("    10 ! V6O13 (vanadium oxide) (LiyV02.167, 0.05 < y < 1.0)\n", fp);
		fputs("    11 ! LiAl0.2Mn1.8O4F0.2 (Bellcore doped spinel) (0.21 < y < 1.0)\n", fp);
		fputs("    12 ! Albertus NiOOHHy\n", fp);
		fputs("    13 ! Add your own positive electrode\n\n", fp);
		fputs("Density and coulombic capacity for commonly-used materials\n\n", fp);
		fputs("Material      Density (kg/m3)   Coulombic capacity (mAh/g)\n", fp);
		fputs("--------      --------------    -------------------------\n", fp);
		fputs("Li metal       534                 3862.5\n", fp);
		fputs("C6            2260                  372\n", fp);
		fputs("LiMn2O4       4280                  148\n", fp);
		fputs("LiCoO2        5010                  274\n", fp);
		fputs("LiV6O13       3900                  417.4 (based on 0 < y < 8)\n", fp);
		fputs("LiTiS2        2285                  225\n", fp);
		fputs("Cu            8954                  ---\n", fp);
		fputs("Al            2707                  ---\n", fp);
		fputs("Carbon black  1950                  ---\n", fp);
		fputs("PVDF binder   1770                  ---", fp);
		fclose(fp);

	}
}

void lwrite(int a, int chance) {
	for (int i = 0; i < a; i++) {
		FILE *fp = NULL;
		errno_t err;
		if (i == 0) err = fopen_s(&fp, "dualfoil1.txt", "w");
		else if (i == 1) err = fopen_s(&fp, "dualfoil2.txt", "w");
		else if (i == 2) err = fopen_s(&fp, "dualfoil3.txt", "w");
		else if (i == 3) err = fopen_s(&fp, "dualfoil4.txt", "w");
		if (err != 0) cout << "파일 오픈 실패" << endl;
		fputs("50        ! lim,   limit on number of iterations\n", fp);
		fputs("100.0d-06 ! h1,  thickness of negative electrode (m)\n", fp);
		fputs("25.d-06   ! h2,  thickness of separator (m)\n", fp);
		fputs("100.0d-06 ! h3,  thickness of positive electrode (m)\n", fp);
		fputs("25.d-06   ! hcn, thickness of negative current collector (m)\n", fp);
		fputs("25.d-06   ! hcp, thickness of positive current collector (m)\n", fp);
		fputs("80        ! n1,    number of nodes in negative electrode(set=0 if in foil mode)\n", fp);
		fputs("40        ! n2,    number of nodes in separator\n", fp);
		fputs("80        ! n3,    number of nodes in positive electrode\n", fp);
		fputs("100       ! n4, number of nodes in solid particle\n", fp);
		fputs("0	    ! mvdc1, flag for variable solid diff coeff in anode\n", fp);
		fputs("0         ! mvdc3, flag for variable solid diff coeff in cathode\n", fp);
		fputs("20	    ! lims, number of iterations for solid phase convergence\n", fp);
		fputs("298.d0    ! T      temperature (K)\n", fp);
		fputs("1000.0    ! xi(1,1), initial salt concentration (mol/m3), 1200 needed for constant load short circuit\n", fp);
		fputs("0.6      ! x,     initial stoichiometric parameter for neg. (ignored if n1=0) 0.67\n", fp);
		fputs("0.5       ! y,     initial stoichiometric parameter for positive based on formula unit where 0<y<1\n", fp);
		fputs("30.0d0    ! tmmax, maximum time step size (s)\n", fp);
		fputs("3.9d-14   ! dfs1,  (ignored in Foil mode) diffusion coef. in negative solid (m2/s) 0.58d-14,\n", fp);
		fputs("1.0d-13   ! dfs3,  diffusion coef. in positive solid (m2/s) 0.8d-14, 3.d-14\n", fp);
		fputs("10.0d-6   ! Rad1,  radius of negative particles (m) (ignored in Foil mode) 0.0000042, 0.0000078\n", fp);
		fputs("10.0d-6   ! Rad3,  radius of positive particles (m) 0.000002, 17\n", fp);
		fputs("0.3       ! ep1,   volume fraction of electrolyte in negative electrode\n", fp);
		fputs("0.0d0     ! epp1,  volume fraction of polymer in negative electrode\n", fp);
		fputs("0.1       ! epf1,  volume fraction of inert filler in negative electrode\n", fp);
		fputs("0.0d0     ! epg1,  volume fraction of gas in negative\n", fp);
		fputs("1.0       ! ep2,   ep2+epp2=1.0  volume fraction of electrolyte in separator\n", fp);
		fputs("0.0d0     ! epp2,  volume fraction of polymer in separator\n", fp);
		fputs("0.0d0     ! epg2,  volume fraction gas in separator\n", fp);
		fputs("0.3       ! ep3,   volume fraction of electrolyte in positive electrode\n", fp);
		fputs("0.0d0     ! epp3,  volume fraction of polymer in positive electrode\n", fp);
		fputs("0.2       ! epf3,  volume fraction of inert filler in positive electrode\n", fp);
		fputs("0.0d0     ! epg3,  volume fraction of gas in positive\n", fp);
		fputs("100.0d0   ! sig1,  conductivity of negative matrix (S/m) (ignored in Foil mode) 124.28\n", fp);
		fputs("10.0d0    ! sig3,  conductivity of positive matrix (S/m) 23.43\n", fp);
		fputs("1.0d-5    ! rka1,  rate constant for negative reaction 2d-9\n", fp);
		fputs("3.d-11    ! rka3,  rate constant for positive reaction, changed from 3 to 4 4d-9\n", fp);
		fputs("0.001d0   ! ranode, anode film resistance (ohm-m2) 0.88d-2\n", fp);
		fputs("0.000d0   ! rcathde,  cathode film resistance (ohm-m2) 2.0d-2 1.0d-2, 1.2d-2\n", fp);
		fputs("372.d0    ! cot1,  coulombic capacity of negative material (mAh/g) \n", fp);
		fputs("274.d0    ! cot3,  coulombic capacity of positive material (mAh/g)\n", fp);
		fputs("1324.0    ! re,    density of electrolyte (kg/m3)\n", fp);
		fputs("1800.0    ! rs1,   density of negative insertion material (kg/m3)\n", fp);
		fputs("5010.0    ! rs3,   density of positive insertion material (kg/m3)\n", fp);
		fputs("1800.0    ! rf,    density of inert filler (kg/m3)\n", fp);
		fputs("1780.0    ! rpl,   (not used here) density of polymer material (kg/m3)\n", fp);
		fputs("0.0d0     ! rc,    density of inert separator material (kg/m3)\n", fp);
		fputs("8954.0    ! rcn,   density of negative current collector (kg/m3) [copper foil]\n", fp);
		fputs("2707.0    ! rcp,   density of positive current collector (kg/m3) [aluminum foil]\n", fp);
		fputs("0.0d0     ! htc,   heat-transfer coefficient at ends of cell stack (W/m2K) 0.36\n", fp);
		fputs("2000.0d0  ! Cp,    heat capacity of system (J/kg-K) 1200\n", fp);
		fputs("298.d0    ! Tam,   ambient air temperature (K)\n", fp);
		fputs("1         ! ncell, number of cells in a cell stack\n", fp);
		fputs("2         ! lht,   0 uses htc,  1 calcs htc,  2 isothermal\n", fp);
		fputs("1         ! il1,   1 for long print-out  0 for short print-out\n", fp);
		fputs("10        ! il2,   prints every il2 th node in long print-out\n", fp);
		fputs("10        ! il3,   prints every il3 th time step in long print-out\n", fp);
		fputs("1         ! lflag, 0 for electrolyte in separator only, 1 for uniform\n", fp);
		fputs("0         ! imp,   0 for no impedance, 1 for impedance\n", fp);
		fputs("0.0d0     ! capp1, capacitance of negative material (F/m2)\n", fp);
		fputs("0.0d0     ! capp3, capacitance of positive material (F/m2)\n", fp);
		fputs("0         ! lpow   0 for no power peaks, 1 for power peaks\n", fp);
		fputs("0         ! jsol   calculate solid profiles if 1 < jsol < nj\n", fp);
		fputs("0         ! nside  flag to turn on (1) or off (0) side reactions\n", fp);
		fputs("0.0d0     ! rksa1   rate constant side reaction 1 negative (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksc1   rate constant side reaction 1 positive (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksa2   rate constant side reaction 2 negative (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksc2   rate constant side reaction 2 positive (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksa3   rate constant side reaction 3 negative (ignored if nside=0)\n", fp);
		fputs("0.0d0     ! rksc3   rate constant side reaction 3 positive (ignored if nside=0)\n", fp);
		fputs("3         ! nneg   see below\n", fp);
		fputs("11        ! nprop  see below\n", fp);
		fputs("6        ! npos   see below\n", fp);
		char buf[50];
		sprintf_s(buf, sizeof(buf), "%d         ! lcurs, number of current changes\n", chance);
		fputs(buf, fp);

		float cu, tt;
		for (int ch = 0; ch < chance; ch++) {
			cu = cuv[ch][i];
			tt = tv[ch][i];
			char mybuff[50];
			sprintf_s(mybuff, sizeof(mybuff), "%.2fd0  %.1fd0  1  2.0d0  4.4d0\n", cu, tt);
			fputs(mybuff, fp);
		}

		fputs("\n\n\n", fp);
		fputs("	EXPLANATIONS\n", fp);
		fputs("lines 20-22: ep1, epp1, and epf1\n", fp);
		fputs("	Set equal to 0.0 when running in Foil mode (metn = 1)\n\n", fp);
		fputs("line 50: il1", fp);
		fputs("          1 gives long print-out no matter if a run converges or not\n", fp);
		fputs("		   The long print-out stops at t(noncovergence).\n", fp);
		fputs("          0 gives short print-out if a run converges but a long\n", fp);
		fputs("            print-out if the run does not converge.\n\n", fp);
		fputs("line 59: lcurs,  number of current changes\n\n", fp);
		fputs("line 60 onward:  cu(i), tt(i), mc(i), vcutlo(i), vcuthi(i)\n", fp);
		fputs("     cu(i) The ith value of the current (A/m2), potential (V), power (W/m2)\n", fp);
		fputs("           or load (Ohm-m2) of the segment\n", fp);
		fputs("     tt(i) The ith value of the time (min) or cutoff potential (V)\n", fp);
		fputs("           of the segment\n", fp);
		fputs("     mc(i) The mode of the segment; 0 for potentiostatic, 1 for galvanostatic\n", fp);
		fputs("	   for a given time, 2 for galvanostatic to a cutoff potential,\n", fp);
		fputs("	   -1 for galvanostatic for a given time with a tapered current upon\n", fp);
		fputs("	   reaching a cutoff potential, -2 for specified power (in W/m2), and\n", fp);
		fputs("         -3 for specified load (in ohm-m2)\n", fp);
		fputs("	 vcutlo(i) low voltage cutoff for current step\n", fp);
		fputs("	 vcuthi(i) high voltage cutoff for current step\n\n", fp);
		fputs("nneg:\n", fp);
		fputs("    1 ! Li foil\n", fp);
		fputs("    2 ! Carbon (petroleum coke)\n", fp);
		fputs("    3 ! MCMB 2528 graphite (Bellcore) (0.01 < x < 0.90)\n", fp);
		fputs("    4 ! TiS2\n", fp);
		fputs("    5 ! Tungsten oxide (LixWO3 with 0<x<0.67)\n", fp);
		fputs("    6 ! Lonza KS6 graphite (Bellcore)\n", fp);
		fputs("    7 ! Albertus MH\n", fp);
		fputs("    8 ! Add your own negative electrode\n\n", fp);
		fputs("nprop:    1 ! AsF6 in methyl acetate\n", fp);
		fputs("    2 ! Perchlorate in PEO\n", fp);
		fputs("    3 ! Sodium Triflate in PEO\n", fp);
		fputs("    4 ! LiPF6 in PC (Sony cell simulation)\n", fp);
		fputs("    5 ! Perchlorate in PC (West simulation)\n", fp);
		fputs("    6 ! Triflate in PEO\n", fp);
		fputs("    7 ! LiPF6 in EC/DMC and p(VdF-HFP) (Bellcore)\n", fp);
		fputs("    8 ! LiPF6 in EC/DMC and p(VdF-HFP) (Bellcore) cell #2\n", fp);
		fputs("    9 ! Ideal ion exchange membrane\n", fp);
		fputs("   10 ! TFSI in PEMO at 40 C (oxymethylene-linked PEO) (LBL)\n", fp);
		fputs("   11 ! LiPF6 in EC:DMC (liquid)\n", fp);
		fputs("   12 ! LiTFSI in PEO at 85 C (LBL)\n", fp);
		fputs("   13 ! Paxton 30% KOH in H2O\n", fp);
		fputs("   14 ! Add your own electrolyte\n\n", fp);
		fputs("npos:\n", fp);
		fputs("    1 ! TiS2\n", fp);
		fputs("    2 ! Spinel Mn2O4 (lower plateau)\n", fp);
		fputs("    3 ! NaCoO2:  Sodium cobalt oxide (P2 phase, 0.3<y<0.92)\n", fp);
		fputs("    4 ! Spinel Mn2O4 (upper plateau) (0.2 < y < 1.0)\n", fp);
		fputs("    5 ! Tungsten oxide (LixWO3 with 0<x<0.67)\n", fp);
		fputs("    6 ! CoO2 (Cobalt dioxide) (0.5 < y < 0.99)\n", fp);
		fputs("    7 ! V2O5 (Vanadium oxide) (0 < y < 0.95)\n", fp);
		fputs("    8 ! Ni0.8Co0.2O2 (Gen 1) (0.4 < y < 0.99)\n", fp);
		fputs("    9 ! Spinel Mn2O4 (Bellcore)\n", fp);
		fputs("    10 ! V6O13 (vanadium oxide) (LiyV02.167, 0.05 < y < 1.0)\n", fp);
		fputs("    11 ! LiAl0.2Mn1.8O4F0.2 (Bellcore doped spinel) (0.21 < y < 1.0)\n", fp);
		fputs("    12 ! Albertus NiOOHHy\n", fp);
		fputs("    13 ! Add your own positive electrode\n\n", fp);
		fputs("Density and coulombic capacity for commonly-used materials\n\n", fp);
		fputs("Material      Density (kg/m3)   Coulombic capacity (mAh/g)\n", fp);
		fputs("--------      --------------    -------------------------\n", fp);
		fputs("Li metal       534                 3862.5\n", fp);
		fputs("C6            2260                  372\n", fp);
		fputs("LiMn2O4       4280                  148\n", fp);
		fputs("LiCoO2        5010                  274\n", fp);
		fputs("LiV6O13       3900                  417.4 (based on 0 < y < 8)\n", fp);
		fputs("LiTiS2        2285                  225\n", fp);
		fputs("Cu            8954                  ---\n", fp);
		fputs("Al            2707                  ---\n", fp);
		fputs("Carbon black  1950                  ---\n", fp);
		fputs("PVDF binder   1770                  ---", fp);
		fclose(fp);
	}
}

void krr(int a, int k, float tiq, int fre) {
	int chance = 1;
	int chance2 = 1;
	int precharge = 4;
	float error = 0;
	int item = 0;
	float time = 0.000;
	float pretime = 0.000;
	float fcu = 0.0;
	int loc = 0;
	int one = 0;
	int prestop = 0;
	int prek = k;
	int preprek = prek;
	double post = 1.0;
	double quantity[100][4];
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 4; j++) quantity[i][j] = 1380.0;
	}
	double current_prediction = 0.0;
	float curr[30] = { 0.0, 11.0, 17.0, 32.0, 44.0, 48.0, 52.0, 67.0, 88.0, 93.0, 100.0, 123.0, 141.0, 156.0, 177.0, 163.0, 144.0, 132.0, 112.0, 99.0, 85.0, 72.0, 58.0, 43.0, 30.0, 21.0, 15.0 };
	float charge[5] = { -80.0, -140.0, -20.0, -120.0, -100.0 };
	cuv[0][0] = cu[0];
	tv[0][0] = 5.0;
	cuv[0][1] = cu[1];
	tv[0][1] = 5.0;
	cuv[0][2] = cu[2];
	tv[0][2] = 5.0;
	cuv[0][3] = cu[3];
	tv[0][3] = 5.0;
	int h = 0;
	cout << "before k " << k << endl;
	while (1) {
		cout << "try" << h + 1 << endl;
		float flt = 0.0000;
		priority_queue<pair<float, int>> volt;
		pretime = time;
		time = time + tv[chance - 1][0];
		char endtime[10];
		sprintf_s(endtime, sizeof(endtime), "%.3f,", time);
		float most = 0.0;
		int vnum = 0;
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				system("cp dualfoil1.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a1.exe");
				system("a1");
			}
			else if (i == 1) {
				system("cp dualfoil2.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a2.exe");
				system("a2");
			}
			else if (i == 2) {
				system("cp dualfoil3.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a3.exe");
				system("a3");
			}
			else {
				system("cp dualfoil4.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a4.exe");
				system("a4");
			}
			cout << "battery" << i + 1 << endl;

			ifstream path("dualfoil5.out");
			if (path.is_open()) {
				string line;
				while (!path.eof()) {
					getline(path, line);
					char *li = _strdup(line.c_str());
					char *context = NULL;
					char *token = strtok_s(li, " ", &context);
					while (token != NULL) {
						if (strcmp(token, endtime) == 0) {
							token = strtok_s(NULL, " ", &context);
							token = strtok_s(NULL, " ", &context);
							char *ss = strtok_s(NULL, ",", &context);
							cout << "time: " << time << endl;
							cout << "volt: " << ss << endl;
							cout << "current: " << cuv[h][i] << endl;
							float flt = atof(ss);
							if (most < flt) {
								most = flt;
								one = i;
							}
							cout << "m : "<< most << " " << one << endl;
							pair<float, int> pp = make_pair(flt, i);
							volt.push(pp);
							vnum++;
						}
						token = strtok_s(NULL, " ", &context);
					}
				}
				path.close();
			}
			if (i == 0) system("cp dualfoil5.out dualfoil1out.txt");
			else if (i == 1) system("cp dualfoil5.out dualfoil2out.txt");
			else if (i == 2) system("cp dualfoil5.out dualfoil3out.txt");
			else system("cp dualfoil5.out dualfoil4out.txt");
		}

		if (vnum != 4) break;

	    double qt;
		for (int y = 0; y < 4; y++) {
			if (cuv[h][y] < 50.0) qt = cuv[h][y] * tv[h][y];
			else if (cuv[h][y] < 100.0) qt = cuv[h][y] * tv[h][y] * 1.1;
			else if (cuv[h][y] < 140.0) qt = cuv[h][y] * tv[h][y] * 1.2;
			else if (cuv[h][y] < 170.0) qt = cuv[h][y] * tv[h][y] * 1.3;
			else if (cuv[h][y] < 200.0) qt = cuv[h][y] * tv[h][y] * 1.4;
			else if (cuv[h][y] < 220.0) qt = cuv[h][y] * tv[h][y] * 1.5;
			else if (cuv[h][y] < 240.0) qt = cuv[h][y] * tv[h][y] * 1.6;
			else qt = cuv[h][y] * tv[h][y] * 1.85;
			if(h>=1) quantity[h][y] = quantity[h - 1][y] - qt;
			else if(h==0) quantity[h][y] = quantity[h][y] - qt;

			if (cuv[h][y] == 0.0 && h > 0) {
				quantity[h][y] = quantity[h - 1][y] + cuv[h - 1][y] * 8.56 * pow(10, -4) + tv[h - 1][y] * 1.835 * pow(10, -3) + tv[h][y] * 9.92 * pow(10, -1) + 4.77 * pow(10, -2);
				if (cuv[h - 1][y] == 0.0 && h>1) {
					quantity[h][y] = quantity[h - 2][y] + cuv[h - 2][y] * 8.56 * pow(10, -4) + tv[h - 2][y] * 1.835 * pow(10, -3) + (tv[h][y] + tv[h - 1][y]) * 9.92 * pow(10, -1) + 4.77 * pow(10, -2);
					if (h > 2) {
						if (cuv[h - 2][y] == 0.0) {
							quantity[h][y] = quantity[h - 3][y] + cuv[h - 3][y] * 8.56 * pow(10, -4) + tv[h - 3][y] * 1.835 * pow(10, -3) + (tv[h][y] + tv[h - 1][y] + tv[h - 2][y]) * 9.92 * pow(10, -1) + 4.77 * pow(10, -2);
						}
					}
				}
			}
		}

		double tq = 0.0;
		double d = 0.0;
		double e = 0.0;
		if (chance % (fre + 1) != fre) {
			if (h == 0) current_prediction = 0.0;
			else current_prediction = curr[item - 1];
			if (h == 0) {
				tq = 0.0;
				d = 0.0;
			}
			else if (h == 1) {
				tq = post - curr[item - 1];
				d = curr[item - 1] - 0.0;
			}
			else {
				tq = post - curr[item - 1];
				d = curr[item - 1] - curr[item - 2];
			}

			error = error + pow(tq, 2);
			e = sqrt(error / float(chance2)) / post;
			d = d*e;
			current_prediction = current_prediction + d;
			post = current_prediction;
			if (post == 0.0) post = 1.0;

			double c_p;
			if (current_prediction < 50.0) {
				c_p = current_prediction*1.0;
			}
			else if (current_prediction < 100.0) {
				c_p = current_prediction*1.1;
			}
			else if (current_prediction < 140.0) {
				c_p = current_prediction*1.2;
			}
			else if (current_prediction < 170.0) {
				c_p = current_prediction*1.3;
			}
			else if (current_prediction < 200.0) {
				c_p = current_prediction*1.4;
			}
			else if (current_prediction < 220.0) {
				c_p = current_prediction*1.5;
			}
			else if (current_prediction < 240.0) {
				c_p = current_prediction*1.6;
			}
			else if (current_prediction < 270.0) {
				c_p = current_prediction*1.85;
			}
			else c_p = current_prediction*2.0;
			cout << "q " << quantity[h][one] << " " << c_p << endl;

			if (quantity[h][one] < c_p) k = 4;
			else k = 1;
		}
		else k = prek;

		preprek = prek;
		prek = k;

		int m = k;
		pair<float, int> t = make_pair(0.0, 0);
		float v[4] = { 0.0, };
		int num[4] = { 0, };
		int vv = 0;
		int nn = 0;
		int length = volt.size();
		if (chance % (fre + 1) == fre) {
			for (int j = 0; j < length; j++) {
				t = volt.top();
				v[vv] = t.first;
				num[nn] = t.second;
				vv++;
				nn++;
				if (k == 1) {
					precharge = t.second;
					break;
				}
			}
		}
		else {
			chance2 = chance2 + 1;
			for (int j = 0; j < length; j++) {
				if (k == 4) {
					t = volt.top();
					v[vv] = t.first;
					num[nn] = t.second;
					vv++;
					nn++;
					volt.pop();
				}
				else {
					t = volt.top();
					v[vv] = t.first;
					num[nn] = t.second;
					cout << "pop " << t.first << " " << t.second << endl;
					volt.pop();
					if (chance != 1 && chance % (fre + 1) == 0 && precharge < 4) {
						num[nn] = precharge;
						if (preprek == 4) num[nn] = one;
					}
					break;
				}
			}
		}

		cout << "k " << k << endl;

		for (int l = 0; l < 4; l++) {	
			if ((num[0]==l && k==1) || k==4) {
				if (chance % (fre + 1) == fre) {
					cuv[chance][l] = charge[loc] / k;
				}
				else {
					cuv[chance][l] = curr[item] / k;
				}
			}
			else cuv[chance][l] = 0.0;
		}

		if (chance % (fre + 1) == fre) loc++;
		else item++;
		if (item == 30) item = 0;
		if (loc == 5) loc = 0;
		for (int tm = 0; tm < 4; tm++) tv[chance][tm] = tiq;

		chance++;
		lwrite(a, chance);
		h++;
	}

	cout << "end" << endl;
}

void krr2(int a, int k, float tiq, int fre) {
	int chance = 1;
	int chance2 = 1;
	int precharge = 4;
	int error = 0;
	int item = 0;
	float time = 0.000;
	float pretime = 0.000;
	float cuv[100][4] = { 0.0 };
	float tv[100][4] = { 0.0 };
	float fcu = 0.0;
	int loc = 0;
	int one = 0;
	int prestop = 0;
	int prek = k;
	int preprek = prek;
	float post = 1.0;
	float quantity[100][4] = { 1380.0 };
	float current_prediction = 0.0;
	float curr[30] = { 0.0, 11.0, 17.0, 32.0, 44.0, 48.0, 52.0, 67.0, 88.0, 93.0, 100.0, 123.0, 141.0, 156.0, 177.0, 163.0, 144.0, 132.0, 112.0, 99.0, 85.0, 72.0, 58.0, 43.0, 30.0, 21.0, 15.0 };
	float charge[5] = { -80.0, -140.0, -20.0, -120.0, -100.0 };
	cuv[0][0] = cu[0];
	tv[0][0] = 5.0;
	cuv[0][1] = cu[1];
	tv[0][1] = 5.0;
	cuv[0][2] = cu[2];
	tv[0][2] = 5.0;
	cuv[0][3] = cu[3];
	tv[0][3] = 5.0;
	int h = 0;
	while (1) {
		cout << "try" << h + 1;
		float flt = 0.0000;
		priority_queue<pair<float, int>> volt;
		pretime = time;
		time = time + tv[chance - 1][0];
		string endtime = to_string(time) + "00,";
		float most = 0.0;
		int vnum = 0;
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				system("cp dualfoil1.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a1.exe");
				system("a1");
			}
			else if (i == 1) {
				system("cp dualfoil2.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a2.exe");
				system("a2");
			}
			else if (i == 2) {
				system("cp dualfoil3.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a3.exe");
				system("a3");
			}
			else {
				system("cp dualfoil4.txt dualfoil5.in");
				system("g77 dualfoil5.1.f -o a4.exe");
				system("a4");
			}
			cout << "battery" << i + 1 << endl;

			ifstream path("dualfoil5.out");
			if (path.is_open()) {
				string line;
				while (!path.eof()) {
					getline(path, line);
					char *li = _strdup(line.c_str());
					char *context = NULL;
					char *token = strtok_s(li, " ", &context);
					while (token != NULL) {
						if (string(token) == endtime) {
							token = strtok_s(NULL, " ", &context);
							token = strtok_s(NULL, " ", &context);
							char *ss = strtok_s(NULL, ",", &context);
							cout << "time: " << time << endl;
							cout << "volt: " << ss << endl;
							cout << "current: " << cuv[h][i] << endl;
							float flt = float(*ss);
							if (most < flt) {
								most = flt;
								one = i;
							}
							pair<float, int> pp = make_pair(flt, i);
							volt.push(pp);
							vnum++;
						}
						token = strtok_s(NULL, " ", &context);
					}
				}
				path.close();
			}
			if (i == 0) system("cp dualfoil5.out dualfoil1out.txt");
			else if (i == 1) system("cp dualfoil5.out dualfoil2out.txt");
			else if (i == 2) system("cp dualfoil5.out dualfoil3out.txt");
			else system("cp dualfoil5.out dualfoil4out.txt");
		}
		if (vnum != 4) break;

		int m = k;
		pair<float, int> t = make_pair(0.0, 0);
		float v[4] = { 0.0, };
		int num[4] = { 0, };
		int vv = 0;
		int nn = 0;
		int length = volt.size();
		if (chance % (fre + 1) == fre) {
			for (int j = 0; j < length; j++) {
				t = volt.top();
				v[vv] = t.first;
				num[nn] = t.second;
				vv++;
				nn++;
				if (m == 1) {
					precharge = t.second;
					break;
				}
			}
		}
		else {
			chance2 = chance2 + 1;
			for (int j = 0; j < length; j++) {
				if (m == 4) {
					t = volt.top();
					v[vv] = t.first;
					num[nn] = t.second;
					vv++;
					nn++;
					volt.pop();
				}
				else {
					t = volt.top();
					v[vv] = t.first;
					num[nn] = t.second;
					volt.pop();
					if (chance != 1 && chance % (fre + 1) == 0 && precharge < 4) num[nn] = precharge;
					break;
				}
			}
		}


		for (int l = 0; l < 4; l++) {

			if ((num[0]==l&&k==1)||k==4) {
				if (chance % (fre + 1) == fre) {
					cuv[chance][l] = charge[loc] / m;
				}
				else {
					cuv[chance][l] = curr[item] / m;
				}
			}
			else cuv[chance][l] = 0.0;
		}

		if (chance % (fre + 1) == fre) loc++;
		else item++;
		if (item == 30) item = 0;
		if (loc == 5) loc = 0;
		for (int tm = 0; tm < 4; tm++) tv[chance][tm] = tiq;

		chance++;
		lwrite(a, chance);
		h++;
	}

	cout << "end" << endl;
}

int main(void) {

	while (1) {
		int batteryNum=4;
		int s, e;
		int f;
		float t;
		cout << "스케줄링 선택(1.설계한 스케줄링 알고리즘, 2. 1RR, 3.nRR): ";
		cin >> s;
		cout << "시간 단위의 크기(time quantum): ";
		cin >> t;
		cout << "방전/충전의 빈도(=방전/충전): ";
		cin >> f;
		cout << "균일성 측정: 균일 1, 불균일 2: ";
		cin >> e;
		if (e == 2) {
			cu[0] = 80.0;
			cu[1] = 230.0;
			cu[2] = -100.0;
			cu[3] = 0.0;
		}

		if (s==1) {
			startkrr(batteryNum, 1);
			krr(batteryNum, 1, t, f);
		}
		else if (s==2) {
			startkrr(batteryNum, 1);
			krr2(batteryNum, 1, t, f);
		}
		else if (s==3) {
			startkrr(batteryNum, 4);
			krr2(batteryNum, 4, t, f);
		}
		else {
			cout << "다시 입력해주세요." << endl;
		}
    }
	return 0;
}



