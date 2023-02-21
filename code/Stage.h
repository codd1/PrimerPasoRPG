#pragma once
class CStage
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual bool Init() = 0;
	virtual void Run() = 0;
};

