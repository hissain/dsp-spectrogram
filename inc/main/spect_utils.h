#ifndef SPECT_UTILS_H
#define SPECT_UTILS_H

#include "arm_math_types.h"

#define SAMPLING_RATE 25000
#define FFT_SIZE 256
#define OVERLAP_FACTOR 0.99
#define NUM_SAMPLES 3002
#define NUM_BINS (ceil((float)(NUM_SAMPLES - FFT_SIZE) / (FFT_SIZE * (1 - OVERLAP_FACTOR))) + 1)

typedef struct {
    int fftSize;
    int binSize;
    float32_t **Sxx;
    float32_t *t;
    float32_t *f;
} SpectrogramOutput;

static float32_t sample_input[3002] = {0.000000, 2.942873, 1.474891, 3.849137, 0.552735, 0.532809, 0.501583, -2.828484, -0.509553, -2.053325, 0.794888, 3.626243, 2.032246, 4.268655, 0.825523, 0.653069, 0.466774, -3.017628, -0.849019, -2.535911, 0.179414, 2.890940, 1.192709, 3.342693, -0.167226, -0.385408, -0.595403, -4.080973, -1.890981, -3.534386, -0.754401, 2.041602, 0.445860, 2.714173, -0.664087, -0.740065, -0.800341, -4.131839, -1.786699, -3.277167, -0.349699, 2.585202, 1.116823, 3.498270, 0.216522, 0.218359, 0.215587, -3.079976, -0.721200, -2.220636, 0.675442, 3.557235, 2.015118, 4.303770, 0.912142, 0.789348, 0.649839, -2.791691, -0.584985, -2.239384, 0.502136, 3.233039, 1.546912, 3.701485, 0.188551, -0.040195, -0.268066, -3.778484, -1.619737, -3.300138, -0.562135, 2.187829, 0.542938, 2.760041, -0.670395, -0.798420, -0.909493, -4.289502, -1.989508, -3.520820, -0.629043, 2.276108, 0.784528, 3.149830, -0.140683, -0.140032, -0.136369, -3.418051, -1.038224, -2.509869, 0.420130, 3.341241, 1.843035, 4.179255, 0.837822, 0.766805, 0.679558, -2.710336, -0.453727, -2.061003, 0.723821, 3.493376, 1.840358, 4.021820, 0.528968, 0.313089, 0.090620, -3.422046, -1.273096, -2.970631, -0.256758, 2.462589, 0.781242, 2.956861, -0.519229, -0.696140, -0.858271, -4.290404, -2.042520, -3.624825, -0.781850, 2.077780, 0.544872, 2.873919, -0.447000, -0.470236, -0.483460, -3.774692, -1.396833, -2.862837, 0.080292, 3.021729, 1.550622, 3.920160, 0.617551, 0.589987, 0.549974, -2.789934, -0.481667, -2.036675, 0.799907, 3.619597, 2.014019, 4.239248, 0.785547, 0.603396, 0.408472, -3.083371, -0.920787, -2.612168, 0.100274, 2.810590, 1.112849, 3.265033, -0.241034, -0.453835, -0.656958, -4.134364, -1.935081, -3.568249, -0.777329, 2.030139, 0.446063, 2.726050, -0.640753, -0.705836, -0.755887, -4.078150, -1.724885, -3.208536, -0.275771, 2.662966, 1.196716, 3.578608, 0.295599, 0.294481, 0.287204, -3.014467, -0.663161, -2.171285, 0.715055, 3.586273, 2.032951, 4.310027, 0.906713, 0.772305, 0.621563, -2.830597, -0.633696, -2.296859, 0.437066, 3.161827, 1.471032, 3.622556, 0.108241, -0.120195, -0.346057, -3.852776, -1.688784, -3.362475, -0.616492, 2.142735, 0.507981, 2.735967, -0.683048, -0.799429, -0.898770, -4.267366, -1.956379, -3.477387, -0.576293, 2.337138, 0.852499, 3.223324, -0.063237, -0.060308, -0.055973, -3.338763, -0.961720, -2.437734, 0.486337, 3.400145, 1.893331, 4.219916, 0.868049, 0.785802, 0.687021, -2.714576, -0.469596, -2.088140, 0.686051, 3.445653, 1.783728, 3.957503, 0.458375, 0.237624, 0.011880, -3.502292, -1.353194, -3.048903, -0.331570, 2.392935, 0.718169, 2.901681, -0.565332, -0.732185, -0.883451, -4.304276, -2.044742, -3.615333, -0.760879, 2.109799, 0.587249, 2.925783, -0.386766, -0.402940, -0.410466, -3.697578, -1.317251, -2.782448, 0.159772, 3.098627, 1.623276, 3.987044, 0.677293, 0.641231, 0.591675, -2.758659, -0.461479, -2.028004, 0.796810, 3.604930, 1.988027, 4.202481, 0.738833, 0.547634, 0.344936, -3.153426, -0.995826, -2.690582, 0.020046, 2.730397, 1.034317, 3.189849, -0.311288, -0.517695, -0.712965, -4.181453, -1.972194, -3.594605, -0.792391, 2.026686, 0.454319, 2.745846, -0.609898, -0.664512, -0.704957, -4.018721, -1.658239, -3.136056, -0.198936, 2.742399, 1.277104, 3.658264, 0.372871, 0.367647, 0.354705, -2.953968, -0.610989, -2.128552, 0.747377, 3.607632, 2.042826, 4.308207, 0.893239, 0.747464, 0.585926, -2.876366, -0.688580, -2.359674, 0.367616, 3.087230, 1.392862, 3.542494, 0.027972, -0.198997, -0.421614, -3.923608, -1.753355, -3.419372, -0.664487, 2.104557, 0.480452, 2.719716, -0.687646, -0.792398, -0.880200, -4.237587, -1.916081, -3.427418, -0.517758, 2.403129, 0.924461, 3.299715, 0.016028, 0.020092, 0.023879, -3.261212, -0.888046, -2.369518, 0.547562, 3.453215, 1.937074, 4.253409, 0.890525, 0.796913, 0.686462, -2.726854, -0.493269, -2.122715, 0.641217, 3.391641, 1.721645, 3.888669, 0.384189, 0.159728, -0.068016, -3.582617, -1.432210, -3.124891, -0.402898, 2.327679, 0.660391, 2.852650, -0.604543, -0.760869, -0.900939, -4.310132, -2.038901, -3.597914, -0.732294, 2.149075, 0.636296, 2.983546, -0.321446, -0.331507, -0.334413, -3.618577, -1.236910, -2.702488, 0.237569, 3.172745, 1.692124, 4.049118, 0.731331, 0.685966, 0.626315, -2.734970, -0.449188, -2.027417, 0.785666, 3.582423, 1.954519, 4.158726, 0.685696, 0.486373, 0.276785, -3.227085, -1.073393, -2.770409, -0.060250, 2.651157, 0.957912, 3.117901, -0.377214, -0.576265, -0.763002, -4.221763, -2.002013, -3.613206, -0.799521, 2.031348, 0.470585, 2.773365, -0.571561, -0.616479, -0.647995, -3.954165, -1.587391, -3.060470, -0.120375, 2.822684, 1.357151, 3.736418, 0.447419, 0.437133, 0.417679, -2.899087, -0.565233, -2.092850, 0.772291, 3.621086, 2.044605, 4.298330, 0.871927, 0.715043, 0.543142, -2.928536, -0.749118, -2.427204, 0.294386, 3.010022, 1.313223, 3.462108, -0.051496, -0.275790, -0.494046, -3.990269, -1.812769, -3.470323, -0.705773, 2.073671, 0.460642, 2.711445, -0.684262, -0.777300, -0.853875, -4.200464, -1.869006, -3.371347, -0.453856, 2.473363, 0.999659, 3.378231, 0.096265, 0.100222, 0.102264, -3.186169, -0.817977, -2.305918, 0.603257, 3.499993, 1.973855, 4.279404, 0.905143, 0.799846, 0.677838, -2.747044, -0.524559, -2.164437, 0.590045, 3.332002, 1.654749, 3.816015, 0.307355, 0.080282, -0.148457, -3.662215, -1.509335, -3.197868, -0.470294, 2.267424, 0.608541, 2.810255, -0.636516, -0.781870, -0.910366, -4.307908, -2.025016, -3.572634, -0.696317, 2.195193, 0.691461, 3.046634, -0.251840, -0.256726, -0.256116, -3.538482, -1.156680, -2.623816, 0.313108, 3.243368, 1.756399, 4.105740, 0.779024, 0.723841, 0.653403, -2.719111, -0.444987, -2.034827, 0.766725, 3.552247, 1.913870, 4.108424, 0.626963, 0.420074, 0.204608, -3.303602, -1.152668, -2.850804, -0.140209, 2.573768, 0.884429, 3.049917, -0.438296, -0.629016, -0.806274, -4.254896, -2.024137, -3.623903, -0.798439, 2.044005, 0.494617, 2.808316, -0.526507, -0.562153, -0.585717, -3.885120, -1.513144, -2.982455, -0.040317, 2.902975, 1.436095, 3.812297, 0.518770, 0.502070, 0.475115, -2.850372, -0.526313, -2.064594, 0.789127, 3.626592, 2.038362, 4.280500, 0.842848, 0.675465, 0.493740, -2.986585, -0.814615, -2.498807, 0.218318, 2.930924, 1.232894, 3.382206, -0.129114, -0.349736, -0.562720, -4.052081, -1.866447, -3.514698, -0.740206, 2.050352, 0.448779, 2.711245, -0.672834, -0.754487, -0.819871, -4.156367, -1.815601, -3.309811, -0.385371, 2.547233, 1.077276, 3.458089, 0.176571, 0.179407, 0.178483, -3.114413, -0.752277, -2.247611, 0.653000, 3.539937, 2.003275, 4.297624, 0.911945, 0.794832, 0.661140, -2.774938, -0.563097, -2.212769, 0.532640, 3.267183, 1.583738, 3.740275, 0.228453, -0.000101, -0.228335, -3.740277, -1.583767, -3.267136, -0.532805, 2.212893, 0.563067, 2.774935, -0.661024, -0.794911, -0.911830, -4.297638, -2.003308, -3.539894, -0.653169, 2.247653, 0.752243, 3.114405, -0.178370, -0.179489, -0.176459, -3.458097, -1.077311, -2.547192, 0.385202, 3.309853, 1.815567, 4.156361, 0.819985, 0.754407, 0.672949, -2.711250, -0.448810, -2.050307, 0.740041, 3.514744, 1.866418, 4.052079, 0.562838, 0.349660, 0.129232, -3.382208, -1.232922, -2.930876, -0.218482, 2.498855, 0.814586, 2.986583, -0.493623, -0.675543, -0.842731, -4.280504, -2.038393, -3.626548, -0.789574, 2.064637, 0.526279, 2.850365, -0.475002, -0.502152, -0.518470, -3.812304, -1.436130, -2.902934, 0.040147, 2.982496, 1.513051, 3.885113, 0.585830, 0.562072, 0.526620, -2.808322, -0.494705, -2.043961, 0.798272, 3.623947, 2.024107, 4.254892, 0.806586, 0.628939, 0.438414, -3.049920, -0.884458, -2.573721, 0.140045, 2.850852, 1.152639, 3.303601, -0.204490, -0.420150, -0.626845, -4.108427, -1.913900, -3.552202, -0.766891, 2.034872, 0.444955, 2.719106, -0.653288, -0.723922, -0.778911, -4.105747, -1.756433, -3.243327, -0.313277, 2.623857, 1.156644, 3.538475, 0.256228, 0.256644, 0.251952, -3.046641, -0.691495, -2.195151, 0.696148, 3.572750, 2.024983, 4.307902, 0.910481, 0.781791, 0.636633, -2.810263, -0.608571, -2.267377, 0.470130, 3.197915, 1.509307, 3.662211, 0.148575, -0.080358, -0.307237, -3.816016, -1.654778, -3.331877, -0.590209, 2.164483, 0.524528, 2.747040, -0.677722, -0.800056, -0.905028, -4.279410, -1.973888, -3.499950, -0.603426, 2.305960, 0.817943, 3.186162, -0.102152, -0.100304, -0.096153, -3.378240, -0.999694, -2.473322, 0.453687, 3.371389, 1.868972, 4.200447, 0.853799, 0.777221, 0.684186, -2.711450, -0.460726, -2.073626, 0.705607, 3.470293, 1.812739, 3.990263, 0.494164, 0.275588, 0.051417, -3.462110, -1.313204, -3.009975, -0.294823, 2.427252, 0.749040, 2.928538, -0.543025, -0.715250, -0.871811, -4.298342, -2.044637, -3.621042, -0.772179, 2.092893, 0.565143, 2.899080, -0.417378, -0.437079, -0.447307, -3.736439, -1.357186, -2.822574, 0.120205, 3.060511, 1.587415, 3.954157, 0.648296, 0.616398, 0.571864, -2.773361, -0.470618, -2.031231, 0.799354, 3.613326, 2.001983, 4.221760, 0.762924, 0.576188, 0.377529, -3.117903, -0.957989, -2.651189, 0.060086, 2.770377, 1.073364, 3.227080, -0.276667, -0.486449, -0.685774, -4.158729, -1.954600, -3.582377, -0.786109, 2.027388, 0.449156, 2.734974, -0.626201, -0.686181, -0.731218, -4.049126, -1.692101, -3.172704, -0.238022, 2.702529, 1.236845, 3.618576, 0.334619, 0.331561, 0.321559, -2.983565, -0.636302, -2.148997, 0.732266, 3.597957, 2.038815, 4.310127, 0.901151, 0.760856, 0.604757, -2.852648, -0.660421, -2.327554, 0.402871, 3.124978, 1.432205, 3.582615, 0.068332, -0.159804, -0.383972, -3.888669, -1.721699, -3.391672, -0.641382, 2.122838, 0.493264, 2.726847, -0.686443, -0.796993, -0.890220, -4.253415, -1.937163, -3.453208, -0.547872, 2.369525, 0.888012, 3.261191, -0.023767, -0.020243, -0.016009, -3.299729, -0.924438, -2.403088, 0.517307, 3.427425, 1.916019, 4.237586, 0.880314, 0.792187, 0.687762, -2.719724, -0.480457, -2.104474, 0.664597, 3.419419, 1.753277, 3.923608, 0.421830, 0.198984, -0.027853, -3.542498, -1.392891, -3.087143, -0.367644, 2.359760, 0.688600, 2.876364, -0.585615, -0.747477, -0.893026, -4.308208, -2.042858, -3.607516, -0.747545, 2.128630, 0.610983, 2.953955, -0.354780, -0.367729, -0.372572, -3.658265, -1.277168, -2.742392, 0.198766, 3.136166, 1.658205, 4.018707, 0.704976, 0.664364, 0.609822, -2.745852, -0.454405, -2.026678, 0.792086, 3.594612, 1.972163, 4.181455, 0.713082, 0.517491, 0.311307, -3.189852, -1.034322, -2.730350, -0.020482, 2.690629, 0.995773, 3.153425, -0.344720, -0.547583, -0.738716, -4.202489, -1.988032, -3.604847, -0.796838, 2.028049, 0.461392, 2.758653, -0.591466, -0.641245, -0.677086, -3.987039, -1.623311, -3.098517, -0.159801, 2.782523, 1.317245, 3.697570, 0.410765, 0.402858, 0.386972, -2.925784, -0.587311, -2.109828, 0.760711, 3.615450, 2.044736, 4.304267, 0.883470, 0.732107, 0.565644, -2.901684, -0.718223, -2.392927, 0.331270, 3.048872, 1.353165, 3.502288, -0.011860, -0.237763, -0.458355, -3.957505, -1.783806, -3.445606, -0.686354, 2.088148, 0.469539, 2.714579, -0.686906, -0.786014, -0.867935, -4.219927, -1.893337, -3.400068, -0.486224, 2.437776, 0.961626, 3.338762, 0.056178, 0.060295, 0.063349, -3.223345, -0.852534, -2.337062, 0.576264, 3.477465, 1.956402, 4.267360, 0.899076, 0.799416, 0.683261, -2.735968, -0.508011, -2.142613, 0.616327, 3.362561, 1.688779, 3.852772, 0.345978, 0.120119, -0.107974, -3.622557, -1.471084, -3.161839, -0.437298, 2.296983, 0.633679, 2.830590, -0.621544, -0.772416, -0.906742, -4.310032, -2.033024, -3.586248, -0.715363, 2.171274, 0.663112, 3.014447, -0.287091, -0.294666, -0.295580, -3.578623, -1.196708, -2.662925, 0.275319, 3.208560, 1.724822, 4.078148, 0.756047, 0.705621, 0.640867, -2.726062, -0.446068, -2.030057, 0.777371, 3.568294, 1.935001, 4.134362, 0.657174, 0.453822, 0.241202, -3.265032, -1.112878, -2.810483, -0.100301, 2.612255, 0.920794, 3.083369, -0.408158, -0.603441, -0.785332, -4.239249, -2.014062, -3.619608, -0.800074, 2.036773, 0.481648, 2.789922, -0.550003, -0.590102, -0.617250, -3.920164, -1.550700, -3.021722, -0.080532, 2.862827, 1.396798, 3.774674, 0.483526, 0.470087, 0.446971, -2.873929, -0.544961, -2.077755, 0.781473, 3.624832, 2.042475, 4.290405, 0.858388, 0.695966, 0.519297, -2.956865, -0.781247, -2.462523, 0.256322, 2.970679, 1.273032, 3.422046, -0.090403, -0.313070, -0.528850, -4.021826, -1.840375, -3.493291, -0.723848, 2.061067, 0.453748, 2.710332, -0.679300, -0.766835, -0.837637, -4.179253, -1.843076, -3.341138, -0.420229, 2.509953, 1.038218, 3.418040, 0.136318, 0.139950, 0.140936, -3.149833, -0.784592, -2.276118, 0.628839, 3.520934, 1.989489, 4.289490, 0.909512, 0.798308, 0.670342, -2.760045, -0.543007, -2.187812, 0.561833, 3.300136, 1.619702, 3.778480, 0.268160, 0.040040, -0.188532, -3.701488, -1.546899, -3.232992, -0.502539, 2.239401, 0.584930, 2.791691, -0.649675, -0.789557, -0.912051, -4.303782, -2.015123, -3.557165, -0.675399, 2.220679, 0.721116, 3.079972, -0.215370, -0.218356, -0.216363, -3.498292, -1.116851, -2.585110, 0.349653, 3.277235, 1.786707, 4.131832, 0.800620, 0.740019, 0.664309, -2.714173, -0.445905, -2.041628, 0.754253, 3.534488, 1.890970, 4.080969, 0.595373, 0.385316, 0.167529, -3.342694, -1.192768, -2.890937, -0.179654, 2.535889, 0.848993, 3.017623, -0.466730, -0.653207, -0.825540, -4.268660, -2.032328, -3.626213, -0.795233, 2.053330, 0.509503, 2.828487, -0.501473, -0.533002, -0.552687, -3.849151, -1.474887, -2.942820, -0.000453, 2.942902, 1.474817, 3.849135, 0.552912, 0.532839, 0.501699, -2.828500, -0.509569, -2.053243, 0.794899, 3.626302, 2.032161, 4.268652, 0.825773, 0.653053, 0.466965, -3.017628, -0.849051, -2.535794, 0.179327, 2.891032, 1.192710, 3.342691, -0.166898, -0.385468, -0.595137, -4.080974, -1.891030, -3.534397, -0.754584, 2.041718, 0.445842, 2.714163, -0.664080, -0.740179, -0.800393, -4.131845, -1.786776, -3.277152, -0.349992, 2.585192, 1.116781, 3.498249, 0.216588, 0.218192, 0.215594, -3.079987, -0.721184, -2.220594, 0.675062, 3.557251, 2.015058, 4.303771, 0.912281, 0.789139, 0.649907, -2.791698, -0.584990, -2.239308, 0.502211, 3.233086, 1.546841, 3.701485, 0.188769, -0.040192, -0.267923, -3.778489, -1.619760, -3.300042, -0.562162, 2.187904, 0.542946, 2.760038, -0.670110, -0.798465, -0.909282, -4.289502, -1.989555, -3.520707, -0.629177, 2.276202, 0.784523, 3.149818, -0.140711, -0.140114, -0.136094, -3.418056, -1.038288, -2.509871, 0.419890, 3.341361, 1.843008, 4.179240, 0.837865, 0.766675, 0.679529, -2.710342, -0.453811, -2.060977, 0.723518, 3.493384, 1.840315, 4.021821, 0.529086, 0.312918, 0.090640, -3.422049, -1.273089, -2.970584, -0.257195, 2.462617, 0.781188, 2.956860, -0.519063, -0.696121, -0.858155, -4.290413, -2.042538, -3.624744, -0.781808, 2.077841, 0.544783, 2.873915, -0.446745, -0.470250, -0.483301, -3.774690, -1.396868, -2.862745, 0.080192, 3.021805, 1.550631, 3.920149, 0.617851, 0.589939, 0.550229, -2.789935, -0.481714, -2.036686, 0.799740, 3.619698, 2.014001, 4.239242, 0.785567, 0.603287, 0.408786, -3.083373, -0.920852, -2.612160, 0.099974, 2.810578, 1.112820, 3.265028, -0.240966, -0.453975, -0.656939, -4.134367, -1.935162, -3.568203, -0.777703, 2.030146, 0.446004, 2.726051, -0.640639, -0.706050, -0.755821, -4.078163, -1.724891, -3.208477, -0.275658, 2.663007, 1.196637, 3.578607, 0.295805, 0.294502, 0.287316, -3.014487, -0.663180, -2.171190, 0.715026, 3.586335, 2.032959, 4.310022, 0.906974, 0.772260, 0.621777, -2.830596, -0.633739, -2.296734, 0.436970, 3.161933, 1.471027, 3.622554, 0.108212, -0.120271, -0.345742, -3.852776, -1.688838, -3.362467, -0.616657, 2.142858, 0.507950, 2.735960, -0.683029, -0.799574, -0.898847, -4.267372, -1.956469, -3.477380, -0.576602, 2.337145, 0.852464, 3.223303, -0.063125, -0.060459, -0.055954, -3.338778, -0.961696, -2.437693, 0.485885, 3.400152, 1.893269, 4.219915, 0.868163, 0.785855, 0.687137, -2.714588, -0.469601, -2.088056, 0.686024, 3.445699, 1.783649, 3.957501, 0.458592, 0.237611, 0.012097, -3.502290, -1.353222, -3.048777, -0.331597, 2.393021, 0.718164, 2.901679, -0.565020, -0.732263, -0.883238, -4.304276, -2.044800, -3.615362, -0.761047, 2.109913, 0.587244, 2.925770, -0.386747, -0.403022, -0.410166, -3.697586, -1.317315, -2.782441, 0.159461, 3.098600, 1.623241, 3.987025, 0.677312, 0.641083, 0.591694, -2.758665, -0.461566, -2.027960, 0.796505, 3.604937, 1.987970, 4.202483, 0.738951, 0.547429, 0.344956, -3.153429, -0.995831, -2.690534, 0.019610, 2.730445, 1.034264, 3.189849, -0.311071, -0.517644, -0.712847, -4.181461, -1.972224, -3.594522, -0.792419, 2.026767, 0.454340, 2.745841, -0.609594, -0.664525, -0.704750, -4.018723, -1.658274, -3.135946, -0.199106, 2.742474, 1.277098, 3.658249, 0.372797, 0.367565, 0.355006, -2.953969, -0.611051, -2.128545, 0.747209, 3.607748, 2.042794, 4.308199, 0.893258, 0.747581, 0.586238, -2.876369, -0.688560, -2.359509, 0.367316, 3.087238, 1.392929, 3.542490, 0.028090, -0.198883, -0.421200, -3.923612, -1.753336, -3.419171, -0.664927, 2.104565, 0.480498, 2.719701, -0.687531, -0.792345, -0.879704, -4.237598, -1.916087, -3.427481, -0.518210, 2.403171, 0.924484, 3.299687, 0.016233, 0.020079, 0.023618, -3.261233, -0.888081, -2.369581, 0.546970, 3.453292, 1.937096, 4.253423, 0.890831, 0.796834, 0.686289, -2.726869, -0.493326, -2.122746, 0.640503, 3.391765, 1.721640, 3.888672, 0.384603, 0.159652, -0.068095, -3.582624, -1.432262, -3.124883, -0.402652, 2.327804, 0.660362, 2.852652, -0.604135, -0.761012, -0.900919, -4.310121, -2.038987, -3.597871, -0.732042, 2.149224, 0.636234, 2.983550, -0.320958, -0.331725, -0.334394, -3.618565, -1.237033, -2.702447, 0.237682, 3.172924, 1.692032, 4.049111, 0.731067, 0.685751, 0.626429, -2.734966, -0.449328, -2.027299, 0.785777, 3.582317, 1.954437, 4.158723, 0.685617, 0.486042, 0.276903, -3.227083, -1.073517, -2.770282, -0.060413, 2.651126, 0.957835, 3.117899, -0.377293, -0.576598, -0.762690, -4.221766, -2.001941, -3.613087, -0.799688, 2.031319, 0.470444, 2.773349, -0.571636, -0.616290, -0.647694, -3.954172, -1.587368, -3.060292, -0.120545, 2.822656, 1.357233, 3.736397, 0.447531, 0.437188, 0.417980, -2.899094, -0.565210, -2.092664, 0.771844, 3.621130, 2.044679, 4.298319, 0.872043, 0.715095, 0.543650, -2.928543, -0.749099, -2.427314, 0.293949, 3.010070, 1.313242, 3.462101, -0.051180, -0.275739, -0.494321, -3.990274, -1.812798, -3.470354, -0.706489, 2.073717, 0.460663, 2.711425, -0.683956, -0.777380, -0.853951, -4.200481, -1.869040, -3.371375, -0.454591, 2.473473, 0.999624, 3.378250, 0.096564, 0.100139, 0.102189, -3.186203, -0.818070, -2.305946, 0.603652, 3.500106, 1.973821, 4.279408, 0.905640, 0.799767, 0.677761, -2.747035, -0.524640, -2.164391, 0.590154, 3.332127, 1.654720, 3.816016, 0.307868, 0.080080, -0.148338, -3.662211, -1.509412, -3.197821, -0.470184, 2.267626, 0.608461, 2.810257, -0.636788, -0.782078, -0.910250, -4.307904, -2.025157, -3.572592, -0.696204, 2.195095, 0.691369, 3.046627, -0.251915, -0.257081, -0.256004, -3.538477, -1.156832, -2.623706, 0.312938, 3.243340, 1.756307, 4.105733, 0.778949, 0.723493, 0.653707, -2.719116, -0.444912, -2.034708, 0.766559, 3.552217, 1.913740, 4.108417, 0.626884, 0.420252, 0.204923, -3.303604, -1.152649, -2.850598, -0.140373, 2.573737, 0.884303, 3.049912, -0.438179, -0.628964, -0.805962, -4.254900, -2.024117, -3.623709, -0.798884, 2.044049, 0.494694, 2.808299, -0.526393, -0.562099, -0.585229, -3.885141, -1.513121, -2.982550, -0.040770, 2.903016, 1.436119, 3.812263, 0.518882, 0.502124, 0.474851, -2.850390, -0.526346, -2.064623, 0.788681, 3.626636, 2.038383, 4.280483, 0.843159, 0.675388, 0.493662, -2.986592, -0.814644, -2.498839, 0.217609, 2.931050, 1.232865, 3.382210, -0.128798, -0.349812, -0.562799, -4.052091, -1.866527, -3.514729, -0.739820, 2.050472, 0.448747, 2.711248, -0.672337, -0.754567, -0.819947, -4.156396, -1.815692, -3.309769, -0.385258, 2.547343, 1.077241, 3.458095, 0.177057, 0.179188, 0.178595, -3.114395, -0.752369, -2.247569, 0.653113, 3.540122, 2.003187, 4.297627, 0.911676, 0.794622, 0.661256, -2.774935, -0.563228, -2.212723, 0.532750, 3.267073, 1.583661, 3.740273, 0.228374, -0.000303, -0.228216, -3.740276, -1.583893, -3.267010, -0.532969, 2.212785, 0.562986, 2.774931, -0.661101, -0.795251, -0.911523, -4.297635, -2.003231, -3.539780, -0.653338, 2.247625, 0.752093, 3.114384, -0.178445, -0.179297, -0.176160, -3.458105, -1.077288, -2.547014, 0.385032, 3.309825, 1.815419, 4.156343, 0.820099, 0.754460, 0.673255, -2.711255, -0.448789, -2.050111, 0.739599, 3.514790, 1.866487, 4.052072, 0.562956, 0.349710, 0.129745, -3.382212, -1.232903, -2.930987, -0.218918, 2.498902, 0.814605, 2.986573, -0.493505, -0.675491, -0.843003, -4.280514, -2.038425, -3.626577, -0.790020, 2.064681, 0.526302, 2.850337, -0.474700, -0.502233, -0.518732, -3.812325, -1.436165, -2.902961, 0.039410, 2.982605, 1.513074, 3.885131, 0.586130, 0.561991, 0.526545, -2.808349, -0.494738, -2.043990, 0.798662, 3.624066, 2.024075, 4.254895, 0.806898, 0.628862, 0.438335, -3.049928, -0.884535, -2.573673, 0.140155, 2.850978, 1.152611, 3.303602, -0.203977, -0.420354, -0.626727, -4.108421, -1.913981, -3.552156, -0.766780, 2.035066, 0.444870, 2.719109, -0.653555, -0.724136, -0.778797, -4.105742, -1.756583, -3.243285, -0.313164, 2.624035, 1.156551, 3.538466, 0.256154, 0.256425, 0.252065, -3.046636, -0.691643, -2.195038, 0.695980, 3.572649, 2.024896, 4.307898, 0.910404, 0.781452, 0.636943, -2.810261, -0.608501, -2.267253, 0.469966, 3.197884, 1.509181, 3.662209, 0.148496, -0.080181, -0.306921, -3.816018, -1.654758, -3.331752, -0.590374, 2.164453, 0.524396, 2.747030, -0.677606, -0.799872, -0.904722, -4.279416, -1.973866, -3.499766, -0.603877, 2.306002, 0.818024, 3.186141, -0.102040, -0.100249, -0.095667, -3.378261, -0.999671, -2.473418, 0.453235, 3.371431, 1.868994, 4.200430, 0.854103, 0.777274, 0.684875, -2.711462, -0.460705, -2.073656, 0.705167, 3.470416, 1.812759, 3.990257, 0.494479, 0.275638, 0.051338, -3.462113, -1.313280, -3.010007, -0.295259, 2.427377, 0.749060, 2.928540, -0.542713, -0.715198, -0.871888, -4.298353, -2.044722, -3.621072, -0.772068, 2.093008, 0.565166, 2.899084, -0.417077, -0.437297, -0.447382, -3.736460, -1.357280, -2.822602, 0.120318, 3.060621, 1.587322, 3.954162, 0.648597, 0.616181, 0.571788, -2.773357, -0.470705, -2.031260, 0.799465, 3.613446, 2.001900, 4.221762, 0.762846, 0.575984, 0.377450, -3.117902, -0.958066, -2.651062, 0.060195, 2.770662, 1.073287, 3.227081, -0.276746, -0.486653, -0.685460, -4.158727, -1.954681, -3.582257, -0.785998, 2.027358, 0.449070, 2.734959, -0.626277, -0.686397, -0.730916, -4.049121, -1.692078, -3.172594, -0.237909, 2.702502, 1.236752, 3.618554, 0.334544, 0.331616, 0.321859, -2.983560, -0.636279, -2.148883, 0.731818, 3.597929, 2.038728, 4.310114, 0.901074, 0.760908, 0.605069, -2.852656, -0.660401, -2.327429, 0.402433, 3.124947, 1.432224, 3.582611, 0.068253, -0.159753, -0.383656, -3.888674, -1.721679, -3.391703, -0.641821, 2.122807, 0.493285, 2.726835, -0.686135, -0.796940, -0.889914, -4.253431, -1.937141, -3.453236, -0.548323, 2.369636, 0.888035, 3.261170, -0.023468, -0.020188, -0.016084, -3.299750, -0.924531, -2.403116, 0.516856, 3.427537, 1.916042, 4.237590, 0.880619, 0.792239, 0.687685, -2.719735, -0.480539, -2.104504, 0.663608, 3.419543, 1.753297, 3.923609, 0.422146, 0.198782, -0.027932, -3.542502, -1.392967, -3.087175, -0.367535, 2.359885, 0.688521, 2.876365, -0.585303, -0.747685, -0.893104, -4.308205, -2.042944, -3.607545, -0.747433, 2.128744, 0.610893, 2.953959, -0.354855, -0.367947, -0.372647, -3.658260, -1.277262, -2.742283, 0.198879, 3.136276, 1.658112, 4.018713, 0.704901, 0.664148, 0.610125, -2.745848, -0.454492, -2.026560, 0.792197, 3.594582, 1.972082, 4.181447, 0.713004, 0.517287, 0.311622, -3.189851, -1.034303, -2.730223, -0.020373, 2.690598, 0.995697, 3.153421, -0.344799, -0.548042, -0.738403, -4.202487, -1.988011, -3.604727, -0.797282, 2.028019, 0.461305, 2.758637, -0.591542, -0.641191, -0.676785, -3.987059, -1.623288, -3.098408, -0.160254, 2.782496, 1.317269, 3.697549, 0.410690, 0.402913, 0.387273, -2.925802, -0.587289, -2.109856, 0.760264, 3.615421, 2.044758, 4.304256, 0.883780, 0.732159, 0.565956, -2.901691, -0.718204, -2.392958, 0.330833, 3.048998, 1.353184, 3.502283, -0.011544, -0.237713, -0.458434, -3.957510, -1.783787, -3.445637, -0.686794, 2.088269, 0.469560, 2.714582, -0.686599, -0.785961, -0.868011, -4.219944, -1.893427, -3.400096, -0.487240, 2.437886, 0.961650, 3.338768, 0.056477, 0.060075, 0.063275, -3.223366, -0.852626, -2.337090, 0.576377, 3.477577, 1.956313, 4.267364, 0.899382, 0.799205, 0.683183, -2.735965, -0.508093, -2.142643, 0.616437, 3.362685, 1.688702, 3.852774, 0.345899, 0.119917, -0.108053, -3.622556, -1.471161, -3.161713, -0.437189, 2.297108, 0.633600, 2.830592, -0.621622, -0.772625, -0.906434, -4.310029, -2.033110, -3.586133, -0.715251, 2.171246, 0.663021, 3.014452, -0.287166, -0.294885, -0.295281, -3.578618, -1.196684, -2.662815, 0.275432, 3.208532, 1.724730, 4.078130, 0.755972, 0.705406, 0.641171, -2.726058, -0.446047, -2.029938, 0.776928, 3.568264, 1.934920, 4.134355, 0.657096, 0.453873, 0.241517, -3.265036, -1.112859, -2.810356, -0.100738, 2.612224, 0.920814, 3.083363, -0.408236, -0.603390, -0.785020, -4.239258, -2.014042, -3.619340, -0.800519, 2.036744, 0.481670, 2.789906, -0.549700, -0.590048, -0.616949, -3.920184, -1.550677, -3.021750, -0.080986, 2.862936, 1.396821, 3.774653, 0.483826, 0.470141, 0.446896, -2.873947, -0.544939, -2.077783, 0.781027, 3.624950, 2.042496, 4.290408, 0.858698, 0.696017, 0.519219, -2.956871, -0.781325, -2.462554, 0.255885, 2.970805, 1.273051, 3.422047, -0.090087, -0.313272, -0.528929, -4.021832, -1.840454, -3.493322, -0.723738, 2.061188, 0.453664, 2.710335, -0.678993, -0.767048, -0.837713, -4.179249, -1.843167, -3.341166, -0.420116, 2.510063, 1.038125, 3.418045, 0.136990, 0.139731, 0.140861, -3.149828, -0.784684, -2.276006, 0.628952, 3.521048, 1.989400, 4.289494, 0.909436, 0.798098, 0.670652, -2.760042, -0.543088, -2.187689, 0.561943, 3.300104, 1.619625, 3.778481, 0.268081, 0.039838, -0.188215, -3.701487, -1.546880, -3.232866, -0.502430, 2.239370, 0.584850, 2.791682, -0.649752, -0.789766, -0.911743, -4.303778, -2.015101, -3.557051, -0.675849, 2.220650, 0.721024, 3.079952, -0.215444, -0.218301, -0.216065, -3.498287, -1.116828, -2.585000, 0.349200, 3.277207, 1.786730, 4.131814, 0.800544, 0.740072, 0.664614, -2.714187, -0.445884, -2.041358, 0.753811, 3.534458, 1.890990, 4.080962, 0.595688, 0.385366, 0.167845, -3.342698, -1.192748, -2.890969, -0.180090, 2.536015, 0.849012, 3.017617, -0.466416, -0.653155, -0.825617, -4.268670, -2.032307, -3.626242, -0.795679, 2.053446, 0.509525, 2.828448, -0.501171, -0.532948, -0.552762, -3.849171, -1.474980, -2.942848, -0.000907, 2.943012, 1.474840, 3.849140, 0.553213, 0.532622, 0.501624, -2.828517, -0.509658, -2.053272, 0.795010, 3.626420, 2.032182, 4.268654, 0.826085, 0.652847, 0.466887, -3.017626, -0.849128, -2.535826, 0.179436, 2.891159, 1.192634, 3.342692, -0.166583, -0.385671, -0.595216, -4.080972, -1.891110, -3.534275, -0.754474, 2.041837, 0.445757, 2.714167, -0.664156, -0.740393, -0.800090, -4.131841, -1.786867, -3.277041, -0.349879, 2.585165, 1.116687, 3.498255, 0.216513, 0.217973, 0.215894, -3.079982, -0.721391, -2.220482, 0.675175, 3.557223, 2.014970, 4.303757, 0.912204, 0.788929, 0.650217, -2.791695, -0.584970, -2.239184, 0.501773, 3.233054, 1.546764, 3.701480, 0.188690, -0.040141, -0.267607, -3.778488, -1.619741, -3.299917, -0.562601, 2.187874, 0.542966, 2.760028, -0.670188, -0.798413, -0.908976, -4.289516, -1.989533, -3.520593, -0.629627, 2.276174, 0.784546, 3.149797, -0.140412, -0.140060, -0.135795, -3.418077, -1.038265, -2.509898, 0.419438, 3.341334, 1.843030, 4.179222, 0.838169, 0.766729, 0.679453, -2.710355, -0.453790, -2.061007, 0.723077, 3.493506, 1.840335, 4.021807, 0.529401, 0.312968, 0.090561, -3.422053, -1.273165, -2.970615, -0.257631, 2.462742, 0.781208, 2.956862, -0.518750, -0.696327, -0.858232, -4.290424, -2.042623, -3.624774, -0.781697, 2.077956, 0.544805, 2.873920, -0.446444, -0.470468, -0.483376, -3.774685, -1.396962, -2.862772, 0.080306, 3.021914, 1.550537, 3.920154, 0.618152, 0.589723, 0.550154, -2.789931, -0.481802, -2.036569, 0.799851, 3.619817, 2.013918, 4.239244, 0.785488, 0.603082, 0.408708, -3.083371, -0.920929, -2.612034, 0.100083, 2.810546, 1.112744, 3.265029, -0.241044, -0.454178, -0.656625, -4.134366, -1.935243, -3.568082, -0.777592, 2.030116, 0.445918, 2.726036, -0.640715, -0.706265, -0.755518, -4.078158, -1.724868, -3.208366, -0.276111, 2.662979, 1.196543, 3.578586, 0.295730, 0.294557, 0.287616, -3.014482, -0.663158, -2.171076, 0.714578, 3.586306, 2.032764, 4.310009, 0.906897, 0.772312, 0.622088, -2.830604, -0.633719, -2.296609, 0.436533, 3.161901, 1.471046, 3.622550, 0.108528, -0.120220, -0.345426, -3.852781, -1.688818, -3.362498, -0.617096, 2.142828, 0.507971, 2.735950, -0.682721, -0.799521, -0.898923, -4.267387, -1.956446, -3.477408, -0.577053, 2.337256, 0.852487, 3.223282, -0.062826, -0.060404, -0.056029, -3.338799, -0.961790, -2.437721, 0.485434, 3.400264, 1.893292, 4.219919, 0.868468, 0.785643, 0.687060, -2.714600, -0.469684, -2.088087, 0.686134, 3.445823, 1.783669, 3.957502, 0.458907, 0.237409, 0.012018, -3.502300, -1.353299, -3.048808, -0.331488, 2.393146, 0.718086, 2.901680, -0.564708, -0.732470, -0.883315, -4.304273, -2.044886, -3.615246, -0.760935, 2.110027, 0.587154, 2.925774, -0.386822, -0.403240, -0.410241, -3.697581, -1.317409, -2.782332, 0.159574, 3.098572, 1.623148, 3.987030, 0.677237, 0.640867, 0.591997, -2.758661, -0.461653, -2.027843, 0.796616, 3.604907, 1.987889, 4.202475, 0.738873, 0.547225, 0.345271, -3.153428, -0.995812, -2.690408, 0.019719, 2.730413, 1.034188, 3.189844, -0.311150, -0.517593, -0.712534, -4.181459, -1.972204, -3.594401, -0.792862, 2.026737, 0.454146, 2.745825, -0.609670, -0.664472, -0.704448, -4.018742, -1.658251, -3.135836, -0.199559, 2.742447, 1.277121, 3.658227, 0.373096, 0.367619, 0.355306, -2.953988, -0.611028, -2.128573, 0.746761, 3.607719, 2.042815, 4.308187, 0.893568, 0.747374, 0.586550, -2.876377, -0.688639, -2.359697, 0.366879, 3.087364, 1.392853, 3.542486, 0.028406, -0.199085, -0.421673, -3.923617, -1.753414, -3.419357, -0.665367, 2.104687, 0.480416, 2.719718, -0.687224, -0.792557, -0.880162, -4.237615, -1.916176, -3.427369, -0.517533, 2.403282, 0.924391, 3.299718, 0.016532, 0.019859, 0.023917, -3.261254, -0.888174, -2.369470, 0.547647, 3.453405, 1.937007, 4.253407, 0.891136, 0.796623, 0.686597, -2.726852, -0.493408, -2.122624, 0.641162, 3.391889, 1.721562, 3.888667, 0.384130, 0.159450, -0.067779, -3.582618, -1.432339, -3.124757, -0.403089, 2.327929, 0.660282, 2.852644, -0.604602, -0.761220, -0.900610, -4.310133, -2.039073, -3.597755, -0.732491, 2.149054, 0.636143, 2.983531, -0.321409, -0.331944, -0.334095, -3.618586, -1.236892, -2.702337, 0.237229, 3.172759, 1.691940, 4.049092, 0.731369, 0.686074, 0.626733, -2.734981, -0.449199, -2.027180, 0.785334, 3.582438, 1.954357, 4.158716, 0.685931, 0.486347, 0.277218, -3.227088, -1.073402, -2.770155, -0.060849, 2.651252, 0.957950, 3.117894, -0.376979, -0.576291, -0.762377, -4.221776, -2.002024, -3.613266, -0.800132, 2.031436, 0.470574, 2.773333, -0.571333, -0.616506, -0.647393, -3.954192, -1.587461, -3.060456, -0.120998, 2.822766, 1.357140, 3.736376, 0.447831, 0.436970, 0.417528, -2.899112, -0.565300, -2.092836, 0.771397, 3.621247, 2.044595, 4.298336, 0.872353, 0.714888, 0.543181, -2.928550, -0.749177, -2.427189, 0.294604, 3.010196, 1.313165, 3.462107, -0.050864, -0.275942, -0.494006, -3.990280, -1.812877, -3.470231, -0.705828, 2.073838, 0.460580, 2.711444, -0.683649, -0.777593, -0.853647, -4.200456, -1.869130, -3.371263, -0.453913, 2.473584, 0.999531, 3.378229, 0.096116, 0.099920, 0.102488, -3.186172, -0.818162, -2.305835, 0.603201, 3.500220, 1.973733, 4.279393, 0.905181, 0.799556, 0.678070, -2.747045, -0.524721, -2.164268, 0.589716, 3.331939, 1.654642, 3.816011, 0.307395, 0.079878, -0.148022, -3.662215, -1.509297, -3.197695, -0.470622, 2.267439};

void print_array(float32_t *data, int size);
void generateSomeCompositSignal();
void generateCompositSignal(float32_t fs, float32_t freq[], float32_t ampl[], int freqLen, int n_samples, float32_t *freqOut);

void exportSignalData(float32_t *signal, int len, char *filename);
void exportSpectrogramData(const SpectrogramOutput *output, const char *filename);
int getHammingWindow(int len, float32_t *window);

#endif