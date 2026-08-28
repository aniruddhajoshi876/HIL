#include "mex.h"
#include "vvcu_controls_wrapper.h"

#include <string.h>

static void cleanup(void)
{
  vvcu_controls_terminate();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  double *tau;

  if (nrhs == 1 && mxIsChar(prhs[0])) {
    char command[16];
    if (mxGetString(prhs[0], command, sizeof(command)) != 0) {
      mexErrMsgIdAndTxt("virtualvcu:ControlsCommand", "Invalid command.");
    }
    if (strcmp(command, "reset") == 0) {
      vvcu_controls_reset();
      return;
    }
    mexErrMsgIdAndTxt("virtualvcu:ControlsCommand", "Unknown command.");
  }

  if (nrhs != 1 || nlhs > 1 || !mxIsDouble(prhs[0]) || mxIsComplex(prhs[0]) ||
      mxGetNumberOfElements(prhs[0]) != VVCU_CONTROLS_INPUT_COUNT) {
    mexErrMsgIdAndTxt("virtualvcu:ControlsInput",
      "Expected one real double vector with 32 elements.");
  }

  mexAtExit(cleanup);
  plhs[0] = mxCreateDoubleMatrix(VVCU_CONTROLS_TORQUE_COUNT, 1, mxREAL);
  tau = mxGetPr(plhs[0]);
  vvcu_controls_step(mxGetPr(prhs[0]), tau);
}
