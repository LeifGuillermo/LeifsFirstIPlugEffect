#include "LeifsFirstIPlugEffect.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

LeifsFirstIPlugEffect::LeifsFirstIPlugEffect(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    const IRECT b = pGraphics->GetBounds();

    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachSVGBackground(REPEATING_CHEVRONS_BACKGROUND);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    pGraphics->AttachControl(new ITextControl(b.GetMidVPadded(50), "Hello iPlug 2!", IText(50)));
    pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(100).GetVShifted(-100), kGain));
  };
#endif
}

#if IPLUG_DSP
void LeifsFirstIPlugEffect::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kGain)->Value() / 100.;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s] * gain;
    }
  }
}
#endif
