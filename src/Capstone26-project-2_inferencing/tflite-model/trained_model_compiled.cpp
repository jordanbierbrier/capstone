/* Generated by Edge Impulse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
// Generated on: 01.04.2023 16:26:04

#include <stdio.h>
#include <stdlib.h>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#if EI_CLASSIFIER_PRINT_STATE
#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C" {
    extern void ei_printf(const char *format, ...);
}
#else
extern void ei_printf(const char *format, ...);
#endif
#endif

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#endif

#ifndef EI_MAX_SCRATCH_BUFFER_COUNT
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#endif // EI_MAX_SCRATCH_BUFFER_COUNT

#ifndef EI_MAX_OVERFLOW_BUFFER_COUNT
#define EI_MAX_OVERFLOW_BUFFER_COUNT 10
#endif // EI_MAX_OVERFLOW_BUFFER_COUNT

using namespace tflite;
using namespace tflite::ops;
using namespace tflite::ops::micro;

namespace {

constexpr int kTensorArenaSize = 2096;

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) __attribute__((section(".tensor_arena")));
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_RESHAPE, OP_CONV_2D, OP_MAX_POOL_2D, OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  TfLiteType type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
  TfLiteQuantization quantization;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

TfLiteContext ctx{};
TfLiteTensor tflTensors[23];
TfLiteEvalTensor tflEvalTensors[23];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[11];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,650 } };
const TfArray<1, float> quant0_scale = { 1, { 0.04689905047416687, } };
const TfArray<1, int> quant0_zero = { 1, { -6 } };
const TfLiteAffineQuantization quant0 = { (TfLiteFloatArray*)&quant0_scale, (TfLiteIntArray*)&quant0_zero, 0 };
const ALIGN(16) int32_t tensor_data1[4] = { 1, 1, 50, 13, };
const TfArray<1, int> tensor_dimension1 = { 1, { 4 } };
const ALIGN(16) int32_t tensor_data2[4] = { 1, 50, 1, 8, };
const TfArray<1, int> tensor_dimension2 = { 1, { 4 } };
const ALIGN(16) int32_t tensor_data3[4] = { 1, 1, 25, 8, };
const TfArray<1, int> tensor_dimension3 = { 1, { 4 } };
const ALIGN(16) int32_t tensor_data4[4] = { 1, 25, 1, 16, };
const TfArray<1, int> tensor_dimension4 = { 1, { 4 } };
const ALIGN(8) int32_t tensor_data5[2] = { -1, 208, };
const TfArray<1, int> tensor_dimension5 = { 1, { 2 } };
const ALIGN(16) int8_t tensor_data6[8*1*3*13] = { 
  /* [0][0][][] */ -104,-69,-42,28,-3,-57,41,42,-12,-22,48,11,14, 95,-68,-38,13,-2,-71,-81,-34,58,44,-18,47,48, -39,63,-22,-31,-38,-34,-70,-127,77,109,31,19,-5, 
  /* [1][0][][] */ 52,110,-23,-47,-34,50,26,-16,10,43,-29,-67,15, 48,125,-29,-31,-71,53,30,-32,-14,51,-60,-17,-36, 89,127,11,-1,-72,33,75,2,-27,2,-28,7,-23, 
  /* [2][0][][] */ 50,-127,99,34,2,-63,-93,49,40,66,-89,60,16, 123,-64,78,-75,-32,118,-69,7,33,75,-46,-24,-12, 68,-125,92,-37,-21,45,-113,20,105,32,-65,35,-6, 
  /* [3][0][][] */ 4,97,-39,-7,31,-39,-25,-42,75,7,-31,-100,17, 45,93,25,-27,13,-14,-29,22,33,28,-46,-19,9, 39,127,3,-22,-33,-38,-31,7,66,19,-35,-64,-8, 
  /* [4][0][][] */ 95,-1,25,30,-27,-81,1,-11,4,0,19,94,1, 79,127,5,72,-116,-36,-31,-63,-41,59,12,97,76, 4,7,17,12,-6,-86,-11,-72,51,29,32,15,100, 
  /* [5][0][][] */ 13,98,27,88,-93,-72,15,9,21,-42,-4,38,-45, -28,-8,62,63,-22,-96,-42,25,25,13,14,-45,6, 84,-12,16,127,-54,-46,-44,-3,-20,10,38,-81,42, 
  /* [6][0][][] */ 3,26,-36,-34,-46,21,46,24,-23,-7,38,37,-25, -40,127,17,-49,9,0,-1,13,27,-44,37,25,-15, 10,-60,8,-43,-2,16,-19,9,-9,-22,31,23,-10, 
  /* [7][0][][] */ -39,-60,-9,-8,-8,9,31,-2,12,20,12,-3,24, 6,-28,-29,9,-13,-11,47,-3,-25,22,-18,12,28, -24,-127,8,36,-19,-11,59,-33,15,21,9,17,31, 
};
const TfArray<4, int> tensor_dimension6 = { 4, { 8,1,3,13 } };
const TfArray<8, float> quant6_scale = { 8, { 0.0050463248044252396, 0.0053938357159495354, 0.0037225298583507538, 0.0059225559234619141, 0.0041975146159529686, 0.0046868599019944668, 0.0081150652840733528, 0.0078786630183458328, } };
const TfArray<8, int> quant6_zero = { 8, { 0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant6 = { (TfLiteFloatArray*)&quant6_scale, (TfLiteIntArray*)&quant6_zero, 0 };
const ALIGN(16) int32_t tensor_data7[8] = { -2379, -7157, -6725, -5861, -6934, -7887, -2229, -1324, };
const TfArray<1, int> tensor_dimension7 = { 1, { 8 } };
const TfArray<8, float> quant7_scale = { 8, { 0.00023666783818043768, 0.00025296577950939536, 0.0001745831104926765, 0.00027776224305853248, 0.00019685944425873458, 0.00021980928431730717, 0.0003805888700298965, 0.00036950182402506471, } };
const TfArray<8, int> quant7_zero = { 8, { 0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant7 = { (TfLiteFloatArray*)&quant7_scale, (TfLiteIntArray*)&quant7_zero, 0 };
const ALIGN(16) int8_t tensor_data8[16*1*3*8] = { 
  /* [0][0][][] */ -17,37,-41,-103,-31,-100,127,-73, 3,-2,-50,-96,14,-37,14,-61, -8,-38,95,-82,3,15,28,-63, 
  /* [1][0][][] */ -4,19,-72,20,-3,-127,45,-44, -54,-27,-95,-2,-8,-54,0,9, 120,-16,-13,-27,17,3,-72,-23, 
  /* [2][0][][] */ -42,-30,-16,-14,-16,30,-82,-120, -121,-24,-43,-27,-42,13,-49,-49, -69,-127,-25,-66,-89,4,-15,-25, 
  /* [3][0][][] */ -3,-127,26,-79,4,-2,-15,48, 17,6,-6,-2,5,-20,-50,-23, -7,11,-24,0,2,-31,24,-39, 
  /* [4][0][][] */ 26,-106,42,-90,-16,-32,-50,14, -7,-101,22,-127,-21,-21,-74,-2, -11,-60,22,4,-19,-2,-91,-8, 
  /* [5][0][][] */ -6,35,-25,-39,52,35,-127,40, -2,28,-37,-47,27,-21,-100,7, 6,2,5,8,31,44,-124,42, 
  /* [6][0][][] */ 25,-7,21,65,36,7,-107,-69, 11,-25,1,3,6,21,-98,-75, 8,-7,-35,32,20,45,-78,-127, 
  /* [7][0][][] */ 9,-127,-16,-98,-77,-40,-6,12, 2,-89,-10,-99,-67,-46,-6,-9, -4,-62,2,-77,-43,-47,1,7, 
  /* [8][0][][] */ 17,-105,65,-99,-45,-32,16,-2, 30,-127,-60,-113,-13,-9,12,-15, -17,-82,18,-39,-21,72,7,-19, 
  /* [9][0][][] */ -33,-24,-65,-50,82,6,5,-4, -9,-72,-71,-127,-2,69,12,-10, 11,-46,-65,-83,32,8,-31,3, 
  /* [10][0][][] */ 26,-13,-1,-17,19,-7,10,-31, 9,3,7,-9,27,-23,3,-79, 6,-3,-22,-8,-10,-27,8,-127, 
  /* [11][0][][] */ -22,-19,-70,-21,-11,-92,13,-12, -78,126,-79,-16,-25,30,3,62, -127,-13,-122,-25,-7,71,3,10, 
  /* [12][0][][] */ 26,-72,-10,-32,0,36,-18,-17, 24,-121,33,-59,46,35,0,-11, -21,-121,-31,-127,-37,-45,-30,-10, 
  /* [13][0][][] */ 18,70,-63,17,-12,-62,-16,-50, -99,-15,-60,-2,-45,-127,-3,-18, -73,-12,-20,2,-70,-115,3,-9, 
  /* [14][0][][] */ -63,106,127,38,-7,6,3,-68, -50,-40,-15,36,39,24,3,-61, -22,126,91,-24,44,83,59,-54, 
  /* [15][0][][] */ 14,11,-42,61,-46,-38,3,-127, -20,-23,12,-49,-89,-42,25,-44, -19,-36,-32,-93,-105,-117,-17,6, 
};
const TfArray<4, int> tensor_dimension8 = { 4, { 16,1,3,8 } };
const TfArray<16, float> quant8_scale = { 16, { 0.0049600806087255478, 0.0056785237975418568, 0.011530809104442596, 0.012631488032639027, 0.011327733285725117, 0.007232381496578455, 0.0065339431166648865, 0.01549144834280014, 0.0059083560481667519, 0.0067368810996413231, 0.013753575272858143, 0.0058828392066061497, 0.007967713288962841, 0.009135526604950428, 0.0034765633754432201, 0.0093542896211147308, } };
const TfArray<16, int> quant8_zero = { 16, { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant8 = { (TfLiteFloatArray*)&quant8_scale, (TfLiteIntArray*)&quant8_zero, 0 };
const ALIGN(16) int32_t tensor_data9[16] = { -1192, -3927, 1863, -2024, 504, -2958, -2048, 944, 1641, -3108, 95, -3283, 316, -67, -11848, -253, };
const TfArray<1, int> tensor_dimension9 = { 1, { 16 } };
const TfArray<16, float> quant9_scale = { 16, { 0.00023418881755787879, 0.00026810989947989583, 0.00054442393593490124, 0.00059639220125973225, 0.00053483573719859123, 0.00034147486439906061, 0.00030849830363877118, 0.00073142442852258682, 0.00027896137908101082, 0.00031807995401322842, 0.0006493711844086647, 0.00027775659691542387, 0.00037619334761984646, 0.0004313313402235508, 0.00016414496349170804, 0.00044166017323732376, } };
const TfArray<16, int> quant9_zero = { 16, { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
const TfLiteAffineQuantization quant9 = { (TfLiteFloatArray*)&quant9_scale, (TfLiteIntArray*)&quant9_zero, 0 };
const ALIGN(16) int8_t tensor_data10[6*208] = { 
  -45, -5, -35, 12, -10, 19, 41, 1, 22, 29, -4, 11, 13, -54, -22, -14, -13, 8, -46, -13, -22, 22, 16, 14, 13, 40, 2, 4, 25, -93, -56, -84, -43, 6, 4, -20, -34, 13, 8, 8, 14, 21, 7, 7, 32, -48, -31, -9, -53, 5, -5, 6, -38, 12, 23, -5, -4, 11, 20, -7, 11, -18, -22, -5, -39, 3, 0, -18, -63, 9, 7, -38, 4, 10, 12, -12, 14, 28, -18, 18, -35, -10, -33, -32, -68, 1, 10, -41, -19, 11, 12, -24, 15, 10, -13, 22, -12, 0, -56, -14, -67, -6, -2, -52, -26, 11, 5, 5, 12, 20, -1, 16, 2, -37, -8, -20, -53, -4, 3, -28, -36, -17, 12, 4, -62, 23, -10, 13, -22, 10, 26, -14, -5, -8, 12, 13, -21, -85, -27, -4, -67, 22, 4, 7, -12, -2, 16, -7, -11, -6, 3, 16, -20, -84, -12, 16, -35, 27, 7, 10, 3, -12, -3, -11, -18, 6, 14, 2, -21, -24, -23, 4, -5, 30, 12, 14, -22, 1, 17, 1, 1, 23, -22, 1, 6, -12, -21, 0, -4, 54, 18, 18, -36, -12, 6, 25, 20, 22, -25, 11, 8, -30, -42, 14, -7, 33, -23, -24, 
  -13, 26, 10, 13, -17, -41, -42, 14, -19, -22, 10, -3, -33, -28, 3, -28, 3, 27, 15, 15, 1, -40, -28, -9, -27, -46, -3, 18, -35, 32, 2, 37, 17, 31, 19, 9, -11, -23, -14, -38, -23, -42, -2, 16, -70, 15, 12, 37, 8, 25, 7, 9, 15, -19, -34, -39, -18, -30, 1, 17, 10, 17, 12, 28, 7, 13, 3, 13, 18, 2, -18, -16, 13, -15, -6, 20, 35, 17, -8, 6, 18, 10, -16, 9, 23, 7, 2, -39, 15, -16, -17, 15, 16, 12, -4, 11, 16, 2, -66, 25, 26, 4, 4, -60, 20, -13, -28, 19, 8, -1, -2, 18, 23, -6, -57, 30, 11, 14, 11, -127, 5, -16, -10, -57, 4, -14, 10, 6, -22, -21, -45, 43, 18, 18, 10, -73, -16, -26, -3, -52, -3, 1, 21, 11, -55, -16, -40, 30, 7, 2, 9, -27, -3, -11, -4, -61, 2, -25, 5, 17, -42, -17, -34, 24, 3, 4, 22, 7, -8, 6, -11, 5, -14, -35, 9, 11, -50, -24, -35, -2, -9, -17, 28, 3, -12, -22, 6, 8, -20, -30, -69, 16, -46, 1, -16, -40, -17, -36, 47, 10, -4, -23, 18, -2, -13, -66, -50, 2, 
  43, -11, 12, -28, -10, 1, -17, -41, 40, -13, 28, -65, 21, -38, -1, 60, 38, -39, -11, -38, -31, 35, -30, -58, 24, 16, -14, -7, -4, -66, 8, 32, 41, -38, -26, -8, -21, 27, -23, -18, 10, 19, -3, -30, 0, -81, -1, 32, 29, -4, -40, -28, 2, 35, -48, -50, 1, -8, -22, -20, -11, -87, -10, -1, -12, -19, -90, 1, -4, 27, -48, -56, -25, -3, -50, -1, -21, -99, -5, -14, -79, -50, -52, -2, -21, 24, -40, -23, -30, 4, -29, -7, -18, -77, -13, -95, -42, -61, -55, -9, -39, 34, -53, -23, -18, 14, -41, -23, -26, -89, -37, -83, 15, -33, -43, -7, -10, 38, -55, 4, 0, 14, 1, -9, -7, -76, -42, -8, 36, -1, -16, -12, -21, 28, -48, -7, 14, 23, -1, -36, -22, -41, -27, 7, 38, -7, -50, -12, -20, 36, -49, -10, 21, 7, 18, -34, 7, -63, -18, 18, 46, -26, -17, -15, -17, 15, -43, -12, 18, 10, 29, -15, -10, -24, -23, 45, 36, 18, -11, -39, -26, 22, -64, -10, 23, -14, 17, -38, -21, -40, -25, 34, 39, 26, 14, -68, -41, -25, -45, -27, 12, -17, 29, -71, 5, -6, -27, 47, 
  -38, 24, 22, 28, 3, 3, -11, 2, -6, -28, -14, 22, -19, -33, 1, -17, -19, 7, 17, 22, -8, 5, 1, 5, -19, -18, 10, 2, -29, -40, 5, -31, 2, 1, 2, 33, -8, -4, -5, -2, -13, -20, 9, -3, -15, -12, 5, -32, 0, 13, 8, 15, -19, -10, 19, 1, -24, -10, 17, -5, -12, -8, 8, -26, 9, 9, 19, 16, -19, 1, 12, -25, -43, -9, 12, -20, -5, -20, 6, -4, -4, 18, 48, 22, -17, 4, 11, -3, -35, -15, 13, -6, -18, -11, 7, -4, -6, 18, 53, -24, -30, -1, 6, 37, -30, -17, 13, -12, -10, -11, -1, -6, -34, 30, 37, 12, -28, -2, 5, 29, -1, -8, 2, 3, 6, -33, 1, -10, -2, 19, 41, -13, -11, 5, 9, 12, 10, -10, 8, 7, 10, -25, -6, -16, -13, 1, 20, -13, -17, 2, 9, 11, 10, 1, 10, 7, -4, -23, -23, -21, -7, -7, 32, -13, -10, -7, 10, 4, -1, -23, -16, -1, 3, -82, -87, -18, -21, 2, 35, 5, -5, 18, -12, -1, 13, -38, -37, 6, -16, -17, -56, 14, 10, -16, 11, 12, 14, 33, -6, 9, 5, 11, -11, 29, 4, -29, -55, -16, 
  8, -10, 5, -32, 19, -31, 5, -24, 6, 24, 9, -21, 28, 40, -25, 8, 13, -4, -17, -2, 10, -51, -43, -12, 10, -7, 7, -20, 29, 15, -42, 4, 17, 0, -14, -12, 21, -33, -28, 6, 19, 3, 1, -18, 12, -13, -47, 0, 7, 18, -3, 8, 20, -30, -69, 21, 28, -21, -7, -33, 7, -12, -58, -2, 11, -1, 1, -4, 19, -48, -54, 17, 22, -36, 6, -16, 9, -19, -39, -2, 17, -4, -26, -3, 17, -42, -49, 49, 14, -23, 9, -28, 9, -45, -74, -23, 17, 3, -20, 5, 5, -45, -72, 30, 20, -28, -8, -33, 13, -36, -60, -14, -1, 19, 0, -13, 4, -40, -63, 24, 20, -12, 6, -38, 16, -41, -63, -20, 2, 19, -26, -12, -2, -39, -54, 7, 14, 8, 12, 1, 9, -5, -70, -11, 9, 13, -13, 4, -1, -29, -49, -7, 3, -3, 6, -18, 16, -32, -60, -23, 11, 15, -21, 12, 13, -33, -52, -23, 16, -8, 22, 4, 15, 9, -39, -17, 4, 6, -20, -6, 3, -23, -33, -20, 19, 14, 15, -39, 16, -20, -4, -15, 14, -8, 2, 8, -3, -35, -11, -37, 0, 28, 3, -60, 9, -3, -15, -10, 
  -2, -26, 0, -12, 8, 1, -6, 1, -8, -11, -11, -6, 7, 21, 25, -7, -1, -10, 17, -18, 20, 3, 4, 11, 0, -11, -25, -5, 0, -14, 11, -15, -3, -16, 9, -3, 20, -1, 15, 19, 15, 2, -8, 6, 3, 12, 17, -23, 10, -18, -2, -10, 15, -6, 11, 32, 2, 5, -9, 15, -8, 4, 16, -12, -2, -15, -3, -15, 19, 4, 13, 43, -3, 8, -11, 23, -4, 1, 13, -4, 11, -7, -1, -5, 15, -1, 8, 45, 2, 7, 2, 11, -11, 3, 12, -8, 1, -16, 5, -7, 15, 2, 3, 26, 2, 13, 0, 15, -2, 5, 13, 2, 5, -6, 1, -6, 17, 8, -3, 31, 1, 19, 7, 21, 9, 15, 18, 3, 16, -12, -3, -6, 19, 14, 3, 15, 5, 24, -3, 25, 10, 6, 14, -13, 11, -2, 9, -11, 7, 7, -7, 11, -4, 31, -4, 22, 16, 10, 14, -7, 1, 2, -1, -18, 17, 3, -7, -2, -4, 18, -3, 3, 7, 12, 20, -14, 19, -6, 0, -4, 14, 19, -4, 2, 4, 25, -8, 2, 8, 3, 43, -29, -8, 28, -15, 0, 12, 25, -14, 0, 9, 10, -2, 4, 1, 4, 59, 1, 
};
const TfArray<2, int> tensor_dimension10 = { 2, { 6,208 } };
const TfArray<1, float> quant10_scale = { 1, { 0.017500592395663261, } };
const TfArray<1, int> quant10_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant10 = { (TfLiteFloatArray*)&quant10_scale, (TfLiteIntArray*)&quant10_zero, 0 };
const ALIGN(16) int32_t tensor_data11[6] = { -700, -185, 427, 600, 3315, -1656, };
const TfArray<1, int> tensor_dimension11 = { 1, { 6 } };
const TfArray<1, float> quant11_scale = { 1, { 0.00058434554375708103, } };
const TfArray<1, int> quant11_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant11 = { (TfLiteFloatArray*)&quant11_scale, (TfLiteIntArray*)&quant11_zero, 0 };
const TfArray<4, int> tensor_dimension12 = { 4, { 1,1,50,13 } };
const TfArray<1, float> quant12_scale = { 1, { 0.04689905047416687, } };
const TfArray<1, int> quant12_zero = { 1, { -6 } };
const TfLiteAffineQuantization quant12 = { (TfLiteFloatArray*)&quant12_scale, (TfLiteIntArray*)&quant12_zero, 0 };
const TfArray<4, int> tensor_dimension13 = { 4, { 1,1,50,8 } };
const TfArray<1, float> quant13_scale = { 1, { 0.047214720398187637, } };
const TfArray<1, int> quant13_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant13 = { (TfLiteFloatArray*)&quant13_scale, (TfLiteIntArray*)&quant13_zero, 0 };
const TfArray<4, int> tensor_dimension14 = { 4, { 1,50,1,8 } };
const TfArray<1, float> quant14_scale = { 1, { 0.047214720398187637, } };
const TfArray<1, int> quant14_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant14 = { (TfLiteFloatArray*)&quant14_scale, (TfLiteIntArray*)&quant14_zero, 0 };
const TfArray<4, int> tensor_dimension15 = { 4, { 1,25,1,8 } };
const TfArray<1, float> quant15_scale = { 1, { 0.047214720398187637, } };
const TfArray<1, int> quant15_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant15 = { (TfLiteFloatArray*)&quant15_scale, (TfLiteIntArray*)&quant15_zero, 0 };
const TfArray<4, int> tensor_dimension16 = { 4, { 1,1,25,8 } };
const TfArray<1, float> quant16_scale = { 1, { 0.047214720398187637, } };
const TfArray<1, int> quant16_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant16 = { (TfLiteFloatArray*)&quant16_scale, (TfLiteIntArray*)&quant16_zero, 0 };
const TfArray<4, int> tensor_dimension17 = { 4, { 1,1,25,16 } };
const TfArray<1, float> quant17_scale = { 1, { 0.033390045166015625, } };
const TfArray<1, int> quant17_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant17 = { (TfLiteFloatArray*)&quant17_scale, (TfLiteIntArray*)&quant17_zero, 0 };
const TfArray<4, int> tensor_dimension18 = { 4, { 1,25,1,16 } };
const TfArray<1, float> quant18_scale = { 1, { 0.033390045166015625, } };
const TfArray<1, int> quant18_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant18 = { (TfLiteFloatArray*)&quant18_scale, (TfLiteIntArray*)&quant18_zero, 0 };
const TfArray<4, int> tensor_dimension19 = { 4, { 1,13,1,16 } };
const TfArray<1, float> quant19_scale = { 1, { 0.033390045166015625, } };
const TfArray<1, int> quant19_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant19 = { (TfLiteFloatArray*)&quant19_scale, (TfLiteIntArray*)&quant19_zero, 0 };
const TfArray<2, int> tensor_dimension20 = { 2, { 1,208 } };
const TfArray<1, float> quant20_scale = { 1, { 0.033390045166015625, } };
const TfArray<1, int> quant20_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant20 = { (TfLiteFloatArray*)&quant20_scale, (TfLiteIntArray*)&quant20_zero, 0 };
const TfArray<2, int> tensor_dimension21 = { 2, { 1,6 } };
const TfArray<1, float> quant21_scale = { 1, { 0.25382328033447266, } };
const TfArray<1, int> quant21_zero = { 1, { 19 } };
const TfLiteAffineQuantization quant21 = { (TfLiteFloatArray*)&quant21_scale, (TfLiteIntArray*)&quant21_zero, 0 };
const TfArray<2, int> tensor_dimension22 = { 2, { 1,6 } };
const TfArray<1, float> quant22_scale = { 1, { 0.00390625, } };
const TfArray<1, int> quant22_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant22 = { (TfLiteFloatArray*)&quant22_scale, (TfLiteIntArray*)&quant22_zero, 0 };
const TfLiteReshapeParams opdata0 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs0 = { 2, { 0,1 } };
const TfArray<1, int> outputs0 = { 1, { 12 } };
const TfLiteConvParams opdata1 = { kTfLitePaddingSame, 1,1, kTfLiteActRelu, 1,1 };
const TfArray<3, int> inputs1 = { 3, { 12,6,7 } };
const TfArray<1, int> outputs1 = { 1, { 13 } };
const TfLiteReshapeParams opdata2 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs2 = { 2, { 13,2 } };
const TfArray<1, int> outputs2 = { 1, { 14 } };
const TfLitePoolParams opdata3 = { kTfLitePaddingSame, 1,2, 1,2, kTfLiteActNone, { { 0,0, 0, 0 } } };
const TfArray<1, int> inputs3 = { 1, { 14 } };
const TfArray<1, int> outputs3 = { 1, { 15 } };
const TfLiteReshapeParams opdata4 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs4 = { 2, { 15,3 } };
const TfArray<1, int> outputs4 = { 1, { 16 } };
const TfLiteConvParams opdata5 = { kTfLitePaddingSame, 1,1, kTfLiteActRelu, 1,1 };
const TfArray<3, int> inputs5 = { 3, { 16,8,9 } };
const TfArray<1, int> outputs5 = { 1, { 17 } };
const TfLiteReshapeParams opdata6 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs6 = { 2, { 17,4 } };
const TfArray<1, int> outputs6 = { 1, { 18 } };
const TfLitePoolParams opdata7 = { kTfLitePaddingSame, 1,2, 1,2, kTfLiteActNone, { { 0,0, 0, 0 } } };
const TfArray<1, int> inputs7 = { 1, { 18 } };
const TfArray<1, int> outputs7 = { 1, { 19 } };
const TfLiteReshapeParams opdata8 = { { 0, 0, 0, 0, 0, 0, 0, 0, }, 0 };
const TfArray<2, int> inputs8 = { 2, { 19,5 } };
const TfArray<1, int> outputs8 = { 1, { 20 } };
const TfLiteFullyConnectedParams opdata9 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs9 = { 3, { 20,10,11 } };
const TfArray<1, int> outputs9 = { 1, { 21 } };
const TfLiteSoftmaxParams opdata10 = { 1 };
const TfArray<1, int> inputs10 = { 1, { 21 } };
const TfArray<1, int> outputs10 = { 1, { 22 } };
const TensorInfo_t tensorData[] = {
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 656, (TfLiteIntArray*)&tensor_dimension0, 650, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant0))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data1, (TfLiteIntArray*)&tensor_dimension1, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data4, (TfLiteIntArray*)&tensor_dimension4, 16, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 8, {kTfLiteNoQuantization, nullptr}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 312, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant6))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data7, (TfLiteIntArray*)&tensor_dimension7, 32, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant7))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data8, (TfLiteIntArray*)&tensor_dimension8, 384, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant8))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data9, (TfLiteIntArray*)&tensor_dimension9, 64, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant9))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data10, (TfLiteIntArray*)&tensor_dimension10, 1248, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant10))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data11, (TfLiteIntArray*)&tensor_dimension11, 24, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant11))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension12, 650, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant12))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 656, (TfLiteIntArray*)&tensor_dimension13, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant13))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension14, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant14))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 400, (TfLiteIntArray*)&tensor_dimension15, 200, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant15))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension16, 200, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant16))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 400, (TfLiteIntArray*)&tensor_dimension17, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant17))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension18, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant18))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 400, (TfLiteIntArray*)&tensor_dimension19, 208, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant19))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension20, 208, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant20))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 208, (TfLiteIntArray*)&tensor_dimension21, 6, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant21))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension22, 6, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant22))}, },
};const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_CONV_2D, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs3, (TfLiteIntArray*)&outputs3, const_cast<void*>(static_cast<const void*>(&opdata3)), OP_MAX_POOL_2D, },
  { (TfLiteIntArray*)&inputs4, (TfLiteIntArray*)&outputs4, const_cast<void*>(static_cast<const void*>(&opdata4)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs5, (TfLiteIntArray*)&outputs5, const_cast<void*>(static_cast<const void*>(&opdata5)), OP_CONV_2D, },
  { (TfLiteIntArray*)&inputs6, (TfLiteIntArray*)&outputs6, const_cast<void*>(static_cast<const void*>(&opdata6)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs7, (TfLiteIntArray*)&outputs7, const_cast<void*>(static_cast<const void*>(&opdata7)), OP_MAX_POOL_2D, },
  { (TfLiteIntArray*)&inputs8, (TfLiteIntArray*)&outputs8, const_cast<void*>(static_cast<const void*>(&opdata8)), OP_RESHAPE, },
  { (TfLiteIntArray*)&inputs9, (TfLiteIntArray*)&outputs9, const_cast<void*>(static_cast<const void*>(&opdata9)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs10, (TfLiteIntArray*)&outputs10, const_cast<void*>(static_cast<const void*>(&opdata10)), OP_SOFTMAX, },
};
static void* overflow_buffers[EI_MAX_OVERFLOW_BUFFER_COUNT];
static size_t overflow_buffers_ix = 0;
static void * AllocatePersistentBuffer(struct TfLiteContext* ctx,
                                       size_t bytes) {
  void *ptr;
  if (current_location - bytes < tensor_boundary) {
    if (overflow_buffers_ix > EI_MAX_OVERFLOW_BUFFER_COUNT - 1) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d, does not fit in tensor arena and reached EI_MAX_OVERFLOW_BUFFER_COUNT\n",
        (int)bytes);
      return NULL;
    }

    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    ptr = ei_calloc(bytes, 1);
    if (ptr == NULL) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return NULL;
    }
    overflow_buffers[overflow_buffers_ix++] = ptr;
    return ptr;
  }

  current_location -= bytes;

  ptr = current_location;
  memset(ptr, 0, bytes);

  return ptr;
}
typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;
static scratch_buffer_t scratch_buffers[EI_MAX_SCRATCH_BUFFER_COUNT];
static size_t scratch_buffers_ix = 0;

static TfLiteStatus RequestScratchBufferInArena(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  if (scratch_buffers_ix > EI_MAX_SCRATCH_BUFFER_COUNT - 1) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d, reached EI_MAX_SCRATCH_BUFFER_COUNT\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffer_t b;
  b.bytes = bytes;

  b.ptr = AllocatePersistentBuffer(ctx, b.bytes);
  if (!b.ptr) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffers[scratch_buffers_ix] = b;
  *buffer_idx = scratch_buffers_ix;

  scratch_buffers_ix++;

  return kTfLiteOk;
}

static void* GetScratchBuffer(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > (int)scratch_buffers_ix) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}

static TfLiteTensor* GetTensor(const struct TfLiteContext* context,
                               int tensor_idx) {
  return &tflTensors[tensor_idx];
}

static TfLiteEvalTensor* GetEvalTensor(const struct TfLiteContext* context,
                                       int tensor_idx) {
  return &tflEvalTensors[tensor_idx];
}

} // namespace

TfLiteStatus trained_model_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    ei_printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#else
  memset(tensor_arena, 0, kTensorArenaSize);
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;
  ctx.AllocatePersistentBuffer = &AllocatePersistentBuffer;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArena;
  ctx.GetScratchBuffer = &GetScratchBuffer;
  ctx.GetTensor = &GetTensor;
  ctx.GetEvalTensor = &GetEvalTensor;
  ctx.tensors = tflTensors;
  ctx.tensors_size = 23;
  for (size_t i = 0; i < 23; ++i) {
    tflTensors[i].type = tensorData[i].type;
    tflEvalTensors[i].type = tensorData[i].type;
    tflTensors[i].is_variable = 0;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    tflTensors[i].allocation_type = tensorData[i].allocation_type;
#else
    tflTensors[i].allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
    tflTensors[i].bytes = tensorData[i].bytes;
    tflTensors[i].dims = tensorData[i].dims;
    tflEvalTensors[i].dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    if(tflTensors[i].allocation_type == kTfLiteArenaRw){
      uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

     tflTensors[i].data.data =  start;
     tflEvalTensors[i].data.data =  start;
    }
    else {
       tflTensors[i].data.data = tensorData[i].data;
       tflEvalTensors[i].data.data = tensorData[i].data;
    }
#else
    tflTensors[i].data.data = tensorData[i].data;
    tflEvalTensors[i].data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
    tflTensors[i].quantization = tensorData[i].quantization;
    if (tflTensors[i].quantization.type == kTfLiteAffineQuantization) {
      TfLiteAffineQuantization const* quant = ((TfLiteAffineQuantization const*)(tensorData[i].quantization.params));
      tflTensors[i].params.scale = quant->scale->data[0];
      tflTensors[i].params.zero_point = quant->zero_point->data[0];
    }
    if (tflTensors[i].allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tflTensors[i].data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }
  if (tensor_boundary > current_location /* end of arena size */) {
    ei_printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }
  registrations[OP_RESHAPE] = Register_RESHAPE();
  registrations[OP_CONV_2D] = Register_CONV_2D();
  registrations[OP_MAX_POOL_2D] = Register_MAX_POOL_2D();
  registrations[OP_FULLY_CONNECTED] = Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = Register_SOFTMAX();

  for (size_t i = 0; i < 11; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
tflNodes[i].custom_initial_data = nullptr;
      tflNodes[i].custom_initial_data_size = 0;
if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for (size_t i = 0; i < 11; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  0, 
};
TfLiteTensor* trained_model_input(int index) {
  return &ctx.tensors[inTensorIndices[index]];
}

static const int outTensorIndices[] = {
  22, 
};
TfLiteTensor* trained_model_output(int index) {
  return &ctx.tensors[outTensorIndices[index]];
}

TfLiteStatus trained_model_invoke() {
  for (size_t i = 0; i < 11; ++i) {
    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);

#if EI_CLASSIFIER_PRINT_STATE
    ei_printf("layer %lu\n", i);
    ei_printf("    inputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].inputs->size; ix++) {
      auto d = tensorData[tflNodes[i].inputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");

    ei_printf("    outputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].outputs->size; ix++) {
      auto d = tensorData[tflNodes[i].outputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");
#endif // EI_CLASSIFIER_PRINT_STATE

    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus trained_model_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif

  // scratch buffers are allocated within the arena, so just reset the counter so memory can be reused
  scratch_buffers_ix = 0;

  // overflow buffers are on the heap, so free them first
  for (size_t ix = 0; ix < overflow_buffers_ix; ix++) {
    ei_free(overflow_buffers[ix]);
  }
  overflow_buffers_ix = 0;
  return kTfLiteOk;
}
