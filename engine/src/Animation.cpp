#include "Animation.h"
#include "MathUtils.h"
#include <algorithm>
#include "SceneGraph.h"

using namespace engine;

bool keyFrameSort(KeyFrame k1, KeyFrame k2)
{
	return k1.Timestamp < k2.Timestamp;
}

KeyFrame::KeyFrame(GLfloat timestamp, vec3* position, Quaternion* rotation, vec3* scale)
	: Timestamp(timestamp), Position(position), Rotation(rotation), Scale(scale) {}

Animation::Animation(SceneNode* target, GLfloat duration)
	: target(target), time(0), reversed(false), currentKeyFrame(0), isActive(true)
{}

void Animation::SetKeyFrames(const std::vector<KeyFrame>& keys)
{
	keyFrames = keys;
	std::sort(keyFrames.begin(), keyFrames.end(), keyFrameSort);
	totalDuration = keyFrames.back().Timestamp;
}

void Animation::SetReversed(GLboolean reverse)
{
	reversed = reverse;
}

void Animation::SetActive(GLboolean active)
{
	isActive = active;
}

void Animation::Update(const GLfloat deltaTime)
{
	if (!isActive)
		return;

	int ksize = keyFrames.size();

	if (reversed)
		time -= deltaTime;
	else
		time += deltaTime;

	time = Clamp(time, 0, totalDuration);

	int nextKeyFrame = currentKeyFrame + 1;
	if (nextKeyFrame >= ksize || nextKeyFrame < 0)
		nextKeyFrame = currentKeyFrame;

	vec3 p1 = *keyFrames[currentKeyFrame].Position;
	vec3 p2 = *keyFrames[nextKeyFrame].Position;
	vec3 s1 = *keyFrames[currentKeyFrame].Scale;
	vec3 s2 = *keyFrames[nextKeyFrame].Scale;
	Quaternion q1 = *keyFrames[currentKeyFrame].Rotation;
	Quaternion q2 = *keyFrames[nextKeyFrame].Rotation;

	GLfloat duration = fabs(keyFrames[nextKeyFrame].Timestamp - keyFrames[currentKeyFrame].Timestamp);

	GLfloat t = fabs(time - keyFrames[currentKeyFrame].Timestamp) / duration;

	target->transform.Position = Lerp(p1, p2, t);
	target->transform.Scale = Lerp(s1, s2, t);
	target->transform.Rotation = Lerp(q1, q2, t);

	if (!reversed && time > keyFrames[nextKeyFrame].Timestamp)
		currentKeyFrame++;

	if (reversed && time < keyFrames[currentKeyFrame].Timestamp)
		currentKeyFrame--;
}
