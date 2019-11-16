#pragma once

#define USE_TASK_MANAGER

struct Texture;
struct Animation;

class ModuleResources : public Module
{
public:

	Texture *background		= nullptr;
	Texture *parking_lot	= nullptr;
	Texture *robot			= nullptr;
	Texture *zombie			= nullptr;
	Texture *blood			= nullptr;
	Texture *bullet			= nullptr;
	Texture *shot			= nullptr;
	Texture *explosion1		= nullptr;
	Texture *explosion2		= nullptr;
	Texture *explosion3		= nullptr;
	Texture *explosion4		= nullptr;
	Texture *explosion5		= nullptr;
	Texture *explosion6		= nullptr;
	Texture *explosion7		= nullptr;

	bool finishedLoading = false;
private:

	bool init() override;

#if defined(USE_TASK_MANAGER)
	void onTaskFinished(Task *task) override;

	void loadTextureAsync(const char *filename, Texture **texturePtrAddress);
#endif

	struct LoadTextureResult {
		Texture **texturePtr = nullptr;
		Task *task = nullptr;
	};

	LoadTextureResult taskResults[1024] = {};
	int taskCount = 0;
	int finishedTaskCount = 0;
};

