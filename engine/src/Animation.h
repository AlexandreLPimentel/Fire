#pragma once
#include "Quaternion.h"
#include <vector>
#include "Interfaces.h"
#include "SceneGraph.h"

namespace engine
{
	class SceneNode;

	struct KeyFrame
	{
		GLfloat Timestamp;
		vec3* Position;
		Quaternion* Rotation;
		vec3* Scale;

		KeyFrame(GLfloat timestamp, vec3* position, Quaternion* rotation, vec3* scale);
	};

	class Animation : IUpdatable
	{
	public:
		Animation(SceneNode * target, GLfloat duration);

		void SetKeyFrames(const std::vector<KeyFrame>& keys);
		void SetReversed(GLboolean reverse);
		void SetActive(GLboolean active);

		void Update(const GLfloat deltaTime) override;

	private:
		~Animation() = default;

		SceneNode* target;
		std::vector<KeyFrame> keyFrames;
		GLfloat time;
		GLboolean reversed;
		GLint currentKeyFrame;
		GLfloat totalDuration;
		GLboolean isActive;
	};
}
