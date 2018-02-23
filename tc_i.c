#include "tc.h"

//linear interpolating Thermocouple conversion (mv -> temperature)
//the whole curve was deviced into 64 pionts (63 sections)
//within each section, it is linearly intropolated into 256 pieces
//number of points
#define TC_POINTS	64

typedef struct {
	signed long uV_LOW;			//low range of the input voltage, uv
	signed long uV_HIGH;			//high range of the input voltage, uv
	signed long Cx1000[TC_POINTS];	//temperature points, in 0.001 Celsius
} TCCURVE_TYPEDEF;

//TC TYPE B curve
const TCCURVE_TYPEDEF TCB_curve ={
	291,		13820,		{
	249916.0747, 323704.7308, 383399.8668, 435096.9286, 481439.2474, 523865.2027, 563318.3990, 600402.6075,
	635512.0226, 669016.1792, 701160.7584, 732037.5081, 761835.4734, 790670.0534, 818641.4668, 845836.6596,
	872331.0218, 898189.9269, 923470.1060, 948220.8699, 972485.1895, 996300.6468, 1019700.267, 1042713.24,
	1065365.549, 1087680.500, 1109679.183, 1131380.850, 1152803.236, 1173962.825, 1194875.058, 1215554.514,
	1236015.038, 1256269.853, 1276331.638, 1296212.593, 1315924.481, 1335478.664, 1354886.134, 1374157.53,
	1393303.160, 1412333.021, 1431256.820, 1450084.002, 1468823.774, 1487485.140, 1506076.941, 1524607.89,
	1543086.619, 1561521.724, 1579921.805, 1598295.511, 1616651.571, 1634998.822, 1653346.219, 1671702.834,
	1690077.826, 1708480.392, 1726919.679, 1745404.660, 1763943.968, 1782545.676, 1801217.016, 1819964.035
	}
};

//TC TYPE E curve
const TCCURVE_TYPEDEF TCE_curve ={
	-8825,		76373,		{
	-199994.8568, -155413.9404, -120311.6507, -89797.14017, -62144.31199, -36457.63961, -12251.56611, 10846.97938,
	33132.56241,  54701.55179,  75637.89474,  96018.26617,  115911.9562,  135380.9573,  154480.2122,  173257.9857,
	191756.3298,  210011.6123,  228055.0866,  245913.4784,  263609.5729,  281162.7867,  298589.7108,  315904.6161,
	333119.9122,  350246.5549,  367294.3994,  384272.4954,  401189.3275,  418052.9994,  434871.3668,  451652.1219,
	468402.8358,  485130.9629,  501843.8153,  518548.5136,  535251.9201,  551960.5641,  568680.5633,  585417.5512,
	602176.6142,  618962.2462,  635778.3244,  652628.1105,  669514.2805,  686438.9841,  703403.9338,  720410.5214,
	737459.9593,  754553.4395,  771692.3039,  788878.2133,  806113.3051,  823400.3205,  840742.686,   858144.5242,
	875610.5711,  893145.97,    910755.9101,  928445.0738,  946216.8523,  964072.2854,  982008.6763,  1000017.829
	}
};

//TC TYPE J curve
const TCCURVE_TYPEDEF TCJ_curve ={
	-8095,		69553,		{
	-209954.7329, 	-161319.1443, 	-125377.2713, 	-94328.188, 	-66006.6865, 	-39396.0586, 	-14018.0259, 	10481.0009,
	34351.6001, 	57766.0804, 	80815.8996, 	103580.9807, 	126130.5895, 	148524.1166, 	170811.7722, 	193035.2082,
	215228.0755, 	237416.529, 	259619.6924, 	281850.0916, 	304114.07, 		326412.1951, 	348739.6693, 	371086.7536,
	393439.2178, 	415778.8272, 	438083.8756, 	460329.779, 	482489.7371, 	504535.4772, 	526438.0893, 	548168.9648,
	569700.8489, 	591009.0187, 	612072.5979, 	632876.0185, 	653410.6416, 	673676.5479, 	693684.5085, 	713458.1488,
	733036.3141, 	752475.6504, 	771725.6135, 	790866.3801, 	809934.8308, 	829021.4313, 	848197.9726, 	867519.1891,
	887024.3755, 	906739.0042, 	926676.3428, 	946839.0711, 	967220.8989, 	987808.1832, 	1008581.545, 	1029517.489,
	1050590.015, 	1071772.244, 	1093038.028, 	1114363.572, 	1135729.048, 	1157120.214, 	1178530.032, 	1199960.286
	}
};

//TC TYPE K curve
const TCCURVE_TYPEDEF TCK_curve ={
	-5891,		54886,		{
	-199933.0768, -150575.2451, -113763.0804, -82350.5098, -54005.8046, -27642.64, -2596.9005, 21560.5499,
	45266.6358,  68563.5787,  91759.5524,  115132.9671, 138812.4998, 162773.3288, 186889.6891, 211002.3266,
	234975.1352, 258728.1902, 282244.5678, 305555.7412, 328714.9878, 351770.1168, 374745.9372, 397643.2318,
	420454.5865, 443188.2369, 465879.1486, 488551.832,  511167.5967, 533822.5069, 556453.8201, 579089.6491,
	601753.9764, 624467.0969, 647246.042,  670104.9854, 693055.6314, 716107.5846, 739268.7021, 762545.427,
	785943.1044, 809466.2793, 833118.9757, 856904.9591, 880827.9792, 904891.9959, 929101.3869, 953461.1366,
	977977.0079, 1002655.695, 1027504.96,  1052533.747, 1077752.285, 1103172.168, 1128806.414, 1154669.517,
	1180777.469, 1207147.767, 1233799.412, 1260752.873, 1288030.045, 1315654.189, 1343649.845, 1372042.735
	}
};

//TC TYPE N curve
const TCCURVE_TYPEDEF TCN_curve ={
	-3990,		47513,		{
	-199936.0203, -140121.6293, -97536.7363, -61183.9775, -27929.7636, 3763.5144, 34532.2462, 64024.8097,
	92388.9384, 119764.0585, 146278.8297, 172049.5372, 197179.2404, 221757.5765, 245861.1233, 269554.2216,
	292890.1602, 315912.6243, 338657.3095, 361153.6038, 383426.2384, 405496.8097, 427385.0752, 449109.9226,
	470689.917, 492143.3262, 513487.5257, 534737.6871, 555904.6489, 576991.8751, 597991.3994, 618962.8579,
	639882.1303, 660764.9886, 681618.9945, 702451.3011, 723268.6861, 744077.5862, 764884.1314, 785694.1784,
	806513.345, 827347.0442, 848200.5181, 869078.8719, 889987.1081, 910930.1603, 931912.9274, 952940.3078,
	974017.2327, 995148.7013, 1016339.814, 1037595.806, 1058922.082, 1080324.252, 1101808.161, 1123379.928,
	1145045.975, 1166813.065, 1188688.335, 1210679.329, 1232794.034, 1255040.91, 1277428.929, 1299967.607
	}
};

//TC TYPE R curve
const TCCURVE_TYPEDEF TCR_curve ={
	-226,		21103,		{
	-49856.5909, 20230.0519, 72885.154, 118953.0022, 171584.9736, 352775.7078, 1457809.969, 273364.1245,
	308381.6271, 342522.1413, 375925.6641, 408697.1657, 440914.5601, 472635.1945, 503901.0731, 534743.0093,
	565183.8766, 595241.1103, 624928.5939, 654258.0438, 683239.9944, 711884.4667, 740201.3946, 768200.8671,
	795893.2376, 823289.1411, 850399.4522, 877235.2102, 903807.5353, 930127.5516, 956206.3362, 982054.9072,
	1007684.269, 1033105.531, 1058330.122, 1083370.132, 1108238.795, 1132951.184, 1157525.13, 1181982.459,
	1206339.505, 1230600.857, 1254783.571, 1278900.281, 1302963.159, 1326983.992, 1350974.259, 1374945.214,
	1398907.965, 1422873.554, 1446853.033, 1470857.55, 1494898.424, 1518987.224, 1543135.853, 1567356.624,
	1591662.341, 1616066.378, 1640582.761, 1665226.797, 1690052.605, 1715273.705, 1741175.275, 1768123.231
	}
};

//TC TYPE S curve
const TCCURVE_TYPEDEF TCS_curve ={
	-236,		18693,		{
	-50091.9827, 11614.2348, 60010.2905, 102641.2391, 141984.2968, 179146.634, 214788.1708, 249284.8702,
	282896.1485, 315818.5052, 348169.1728, 380036.9964, 411489.6705, 442577.5758, 473337.1699, 503793.9567,
	533965.0579, 563861.411, 593489.6177, 622853.4689, 651955.1719, 680796.3037, 709378.5212, 737704.0515,
	765775.9942, 793598.4621, 821176.5919, 848516.4549, 875624.9006, 902509.364, 929177.6736, 955637.8927,
	981898.2321, 1007967.071, 1033853.125, 1059565.804, 1085115.798, 1110515.938, 1135782.372, 1160936.116,
	1186005.005, 1210993.781, 1235908.262, 1260765.824, 1285578.875, 1310359.583, 1335119.941, 1359871.828,
	1384627.064, 1409397.482, 1434194.978, 1459031.58, 1483919.506, 1508871.225, 1533899.519, 1559017.545,
	1584238.892, 1609577.649, 1635048.46, 1660666.588, 1686477.516, 1712719.172, 1739749.775, 1768045.92
	}
};

//TC TYPE T curve
const TCCURVE_TYPEDEF TCT_curve ={
	-5603,		20872,		{
	-199964.0833, 	-175842.0675, -155172.1893, -136776.8042, -119976.1597, -104378.5072, -89742.64486, -75898.11201,
	-62708.2577,  	-50061.4058, -37875.33829, -26100.31919, -14705.88099, -3636.595872, 7209.741905, 17806.69755,
	28167.24213, 	38308.74415, 48247.19426, 57997.29118, 67572.5248, 76985.25633, 86246.79563, 95367.47555,
	104356.7235, 	113223.1299, 121974.5141, 130617.9871, 139160.0116, 147606.4587, 155962.6625, 164233.471,
	172423.2946, 	180536.1517, 188575.711, 196545.3314, 204448.0988, 212286.8598, 220064.2528, 227782.7363,
	235444.614, 	243052.057, 250607.1232, 258111.7744, 265567.8893, 272977.2745, 280341.6724, 287662.7662,
	294942.1821, 	302181.488, 309382.1906, 316545.7279, 323673.4605, 330766.6588, 337826.4878, 344853.989,
	351850.0594, 	358815.4273, 365750.6259, 372655.9631, 379531.4892, 386376.9612, 393191.8046, 399975.0719
	}
};

//convert uv to index - 6bits:256bits. 6 bits of index and 256bits of interpolation
#define TCB_uv2index(uv)	(((uv) - TCB_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCB_curve.uV_HIGH - TCB_curve.uV_LOW))
#define TCE_uv2index(uv)	(((uv) - TCE_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCE_curve.uV_HIGH - TCE_curve.uV_LOW))
#define TCJ_uv2index(uv)	(((uv) - TCJ_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCJ_curve.uV_HIGH - TCJ_curve.uV_LOW))
#define TCK_uv2index(uv)	(((uv) - TCK_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCK_curve.uV_HIGH - TCK_curve.uV_LOW))
#define TCN_uv2index(uv)	(((uv) - TCN_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCN_curve.uV_HIGH - TCN_curve.uV_LOW))
#define TCR_uv2index(uv)	(((uv) - TCR_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCR_curve.uV_HIGH - TCR_curve.uV_LOW))
#define TCS_uv2index(uv)	(((uv) - TCS_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCS_curve.uV_HIGH - TCS_curve.uV_LOW))
#define TCT_uv2index(uv)	(((uv) - TCT_curve.uV_LOW) * ((TC_POINTS - 1) << 8) / (TCT_curve.uV_HIGH - TCT_curve.uV_LOW))

//256-point interpolation
#define TCB_itp(i6, i256)	(((TCB_curve.Cx1000[i6+1] - TCB_curve.Cx1000[i6]) * i256) >> 8)
#define TCE_itp(i6, i256)	(((TCE_curve.Cx1000[i6+1] - TCE_curve.Cx1000[i6]) * i256) >> 8)
#define TCJ_itp(i6, i256)	(((TCJ_curve.Cx1000[i6+1] - TCJ_curve.Cx1000[i6]) * i256) >> 8)
#define TCK_itp(i6, i256)	(((TCK_curve.Cx1000[i6+1] - TCK_curve.Cx1000[i6]) * i256) >> 8)
#define TCN_itp(i6, i256)	(((TCN_curve.Cx1000[i6+1] - TCN_curve.Cx1000[i6]) * i256) >> 8)
#define TCR_itp(i6, i256)	(((TCR_curve.Cx1000[i6+1] - TCR_curve.Cx1000[i6]) * i256) >> 8)
#define TCS_itp(i6, i256)	(((TCS_curve.Cx1000[i6+1] - TCS_curve.Cx1000[i6]) * i256) >> 8)
#define TCT_itp(i6, i256)	(((TCT_curve.Cx1000[i6+1] - TCT_curve.Cx1000[i6]) * i256) >> 8)

//convert uv to mC(=Cx1000)
signed long TCB_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCB_uv2index(uv);				//convert uv to 6+8bit index
	return TCB_curve.Cx1000[*i6] + TCB_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//convert uv to mC(=Cx1000)
signed long TCE_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCE_uv2index(uv);				//convert uv to 6+8bit index
	return TCE_curve.Cx1000[*i6] + TCE_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//convert uv to mC(=Cx1000)
signed long TCJ_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCJ_uv2index(uv);				//convert uv to 6+8bit index
	return TCJ_curve.Cx1000[*i6] + TCJ_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//convert uv to mC(=Cx1000)
signed long TCK_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCK_uv2index(uv);				//convert uv to 6+8bit index
	return TCK_curve.Cx1000[*i6] + TCK_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//convert uv to mC(=Cx1000)
signed long TCN_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCN_uv2index(uv);				//convert uv to 6+8bit index
	return TCN_curve.Cx1000[*i6] + TCN_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//convert uv to mC(=Cx1000)
signed long TCR_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCR_uv2index(uv);				//convert uv to 6+8bit index
	return TCR_curve.Cx1000[*i6] + TCR_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//convert uv to mC(=Cx1000)
signed long TCS_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCS_uv2index(uv);				//convert uv to 6+8bit index
	return TCS_curve.Cx1000[*i6] + TCS_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//convert uv to mC(=Cx1000)
signed long TCT_uv2c(signed long uv) {
	unsigned char *i256 = (unsigned char *) &uv;			//i256 points to uv - endian dependent
	unsigned char *i6=i256+1;			//i6 = piece-wise index, i256 = index within a piece

	uv = TCT_uv2index(uv);				//convert uv to 6+8bit index
	return TCT_curve.Cx1000[*i6] + TCT_itp(*i6, *i256);	//=piece-wise value + interpolation
}

//helper functions. don't use

#if 0
//print tc tables
void tcb_print(unsigned char points) {
	double start = TCB_table[TC_CURVE1].mV_LOW;
	double end = TCB_table[TC_CURVE2].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type B\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10f\n", (int) TCB_uv2index(start * 1000)/*points*/, start, TCB9_mv2c(start)*1000);
		start+=delta;
	}
}

void tce_print(unsigned char points) {
	double start = TCE_table[TC_CURVE1].mV_LOW;
	double end = TCE_table[TC_CURVE2].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type E\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10f\n", (int) TCE_uv2index(start * 1000)/*points*/, start, TCE9_mv2c(start)*1000);
		start+=delta;
	}
}

void tcj_print(unsigned char points) {
	double start = TCJ_table[TC_CURVE1].mV_LOW;
	double end = TCJ_table[TC_CURVE3].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type J\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10.4f\n", (int) TCJ_uv2index(start * 1000)/*points*/, start, TCJ9_mv2c(start) * 1000);
		start+=delta;
	}
}

void tck_print(unsigned char points) {
	double start = TCK_table[TC_CURVE1].mV_LOW;
	double end = TCK_table[TC_CURVE3].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type K\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10.4f\n", (int) TCK_uv2index(start * 1000)/*points*/, start, TCK9_mv2c(start) * 1000);
		start+=delta;
	}
}

void tcn_print(unsigned char points) {
	double start = TCN_table[TC_CURVE1].mV_LOW;
	double end = TCN_table[TC_CURVE3].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type N\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10.4f\n", (int) TCN_uv2index(start * 1000)/*points*/, start, TCN9_mv2c(start) * 1000);
		start+=delta;
	}
}

void tcr_print(unsigned char points) {
	double start = TCR_table[TC_CURVE1].mV_LOW;
	double end = TCR_table[TC_CURVE4].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type R\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10.4f\n", (int) TCR_uv2index(start * 1000)/*points*/, start, TCR9_mv2c(start) * 1000);
		start+=delta;
	}
}

void tcs_print(unsigned char points) {
	double start = TCS_table[TC_CURVE1].mV_LOW;
	double end = TCS_table[TC_CURVE4].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type S\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10.4f\n", (int) TCS_uv2index(start * 1000)/*points*/, start, TCS9_mv2c(start) * 1000);
		start+=delta;
	}
}

void tct_print(unsigned char points) {
	double start = TCT_table[TC_CURVE1].mV_LOW;
	double end = TCT_table[TC_CURVE2].mV_HIGH;
	double delta = (end - start) / (points - 1);

	printf("TC Type T\n");
	for (; points--; ) {
		printf("count %4d / mv = %10.4f: %10f\n", (int) TCT_uv2index(start * 1000)/*points*/, start, TCT9_mv2c(start) * 1000);
		start+=delta;
	}
}

#endif
