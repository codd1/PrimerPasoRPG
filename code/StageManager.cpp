#include "StageManager.h"
#include "StageEasy.h"
#include "StageNormal.h"
#include "StageHard.h"

DEFINITION_SINGLE(CStageManager)

CStageManager::CStageManager() {

}

CStageManager::~CStageManager() {
    Safe_Delete_VecList(m_vecStage);
}

bool CStageManager::Init()
{
    if (!CreateStage(ST_EASY)) {
        return false;
    }
    if (!CreateStage(ST_NORMAL)) {
        return false;
    }
    if (!CreateStage(ST_HARD)) {
        return false;
    }
    return true;
}

void CStageManager::Run()
{
    m_vecStage[0]->Run();
}

bool CStageManager::CreateStage(STAGE_TYPE eType)
{
    CStage* pStage = NULL;

    switch (eType) {
    case ST_EASY:
        pStage = new CStageEasy;
        break;
    case ST_NORMAL:
        pStage = new CStageNormal;
        break;
    case ST_HARD:
        pStage = new CStageHard;
        break;
    }

    if (!pStage->Init()) {
        SAFE_DELETE(pStage);
        return false;
    }
    m_vecStage.push_back(pStage);

    return true;
}
