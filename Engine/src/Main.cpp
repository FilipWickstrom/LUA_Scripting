#include "PCH.h"
#include "Game.h"

int main()
{
	Game game;
	srand((unsigned int)time(nullptr));

	double start = omp_get_wtime();
	double end = omp_get_wtime() - start;

	while(Graphics::GetDevice()->run()) {
		
		start = omp_get_wtime();
		Graphics::GetDeltaTime() = end;
		game.Run();
		end = omp_get_wtime() - start;
	}

	return 0;
}