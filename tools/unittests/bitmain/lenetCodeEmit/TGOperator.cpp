#include "TGOperator.h"
#include <bmkernel_api.h>
#include <iostream>

TGOperator *TGOperator::makeTGOperator(const onnx::Node &node,
                                       uint64_t offset) {
  uint32_t symbol = node.kind();
  if (symbol == onnx::Symbol("Conv"))
    return new TGConv(node, offset);
  else if (symbol == onnx::Symbol("Relu"))
    return new TGRelu(node, offset);
  else if (symbol == onnx::Symbol("LRN"))
    return new TGLRN(node, offset);
  else if (symbol == onnx::Symbol("MaxPool"))
    return new TGMaxPool(node, offset);
  else if (symbol == onnx::Symbol("Gemm"))
    return new TGGemm(node, offset);
  else if (symbol == onnx::Symbol("Softmax"))
    return new TGSoftmax(node, offset);
  std::cerr << "unsupported node type: " << node.kind().toString() << std::endl;
  return nullptr;
}

TGOperator::TGOperator(const onnx::Node &node) : m_totalSize(0) {
  // TODO cal total size
  //  for (val = inputs and outputs) {
  //    m_totalSize += val.sizes() * sizeof(val.elemType);
  //  }
}

// TGConv
TGConv::TGConv(const onnx::Node &node, uint64_t offset) : TGOperator(node) {
  m_name = std::string("Conv");
}

void TGConv::emit(void) const {
  std::cout << "TGConv::emit" << std::endl;
  bmnet_conv_forward_bmkernel(0,     // gaddr_t             ga_ifmap,
                              0,     // gaddr_t             ga_ofmap,
                              0,     // gaddr_t             ga_weight,
                              0,     // gaddr_t             ga_bias,
                              0,     // gaddr_t             ga_bn_mean,
                              0,     // gaddr_t             ga_bn_variance,
                              0,     // gaddr_t             ga_scale,
                              0,     // gaddr_t             ga_scale_bias,
                              4,     // int                 input_n,
                              3,     // int                 input_c,
                              50,    // int                 input_h,
                              50,    // int                 input_w,
                              1,     // int                 groups,
                              5,     // int                 output_c,
                              5,     // u16                 kh,
                              5,     // u16                 kw,
                              1,     // u16                 dilation_h,
                              1,     // u16                 dilation_w,
                              0,     // u8                  pad_h,
                              0,     // u8                  pad_w,
                              1,     // u8                  stride_h,
                              1,     // u8                  stride_w,
                              false, // int                 result_add,
                              0,     // int                 do_bias,
                              0,     // int                 do_bn,
                              0,     // int                 do_scale,
                              0,     // int                 do_scale_bias,
                              0,     // int                 do_activation,
                              0,     // float               bn_scale,
                              0,     // float               bn_eps,
                              0,     // int                 activation_method,
                              0,     // float               activation_arg[],
                              0,     // gaddr_t             activation_ga_slope,
                              0      //  bool activation_channel_shared
                              );
}

// TGRelu
TGRelu::TGRelu(const onnx::Node &node, uint64_t offset) : TGOperator(node) {
  m_name = std::string("Relu");
}

void TGRelu::TGRelu::emit(void) const {}

// TGLRN
TGLRN::TGLRN(const onnx::Node &node, uint64_t offset) : TGOperator(node) {
  m_name = std::string("LRN");
}

void TGLRN::TGLRN::emit(void) const {}

// TGMaxPool
TGMaxPool::TGMaxPool(const onnx::Node &node, uint64_t offset)
    : TGOperator(node) {
  m_name = std::string("MaxPool");
}

void TGMaxPool::TGMaxPool::emit(void) const {}

// TGGemm
TGGemm::TGGemm(const onnx::Node &node, uint64_t offset) : TGOperator(node) {
  m_name = std::string("Gemm");
}

void TGGemm::TGGemm::emit(void) const {}

// TGSoftmax
TGSoftmax::TGSoftmax(const onnx::Node &node, uint64_t offset)
    : TGOperator(node) {
  m_name = std::string("Softmax");
}

void TGSoftmax::TGSoftmax::emit(void) const {}
