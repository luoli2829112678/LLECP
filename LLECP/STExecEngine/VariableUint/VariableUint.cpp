#include"VariableUint.h"

VariableUint::VariableUint(StructManager* pStructManager,uint32_t nStructInfoID,string VariableName)
{
    nVariableSize = pStructManager->GetStructSize(nStructInfoID);
    sVariableName = VariableName;
    nStructInfoID = nStructInfoID;
    pDataAddr = malloc(nVariableSize);
}

VariableUint::~VariableUint()
{
    free(pDataAddr);
}