#pragma once

namespace engine
{
	class IUpdatable
	{
	protected:
		~IUpdatable() = default;
	public:
		virtual void Update(const GLfloat deltaTime) = 0;
	};
}
