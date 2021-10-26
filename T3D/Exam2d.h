#include "WinGLApplication.h"
#include "Texture.h"
#include "DrawTask.h"

namespace T3D
{
	//! \brief Tutorial1 Driver
	class Exam2d :
		public WinGLApplication
	{
	public:
		Exam2d(void);
		~Exam2d(void) = default;

		bool init();


	private:
		Texture* drawArea;
		DrawTask* drawTask;
	};

}
