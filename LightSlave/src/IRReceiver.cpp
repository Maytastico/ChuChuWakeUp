#include <IRReceiver.h>

IRReceiver::IRReceiver(IRrecv *irRecv)
{
_pIrRecv = irRecv;
}

void IRReceiver::begin()
{
    _pIrRecv->enableIRIn();
}

bool IRReceiver::isDataFetched()
{
    return dataFetched;
}

bool IRReceiver::isDataReady()
{
    bool isReady = _pIrRecv->decode(&_results);

    if (isReady)
    {
      encodedData = _results.value;
      _pIrRecv->resume();
      dataFetched = false;
      return true;
    }
    return false;
}

uint32_t IRReceiver::getEncodedData()
{
    dataFetched = true;
    return encodedData;
}