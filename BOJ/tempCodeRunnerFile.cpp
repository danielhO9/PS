
			++time;
			for (int i = 6; i >= 0; --i) for (int j = 0; j < 8; ++j) wall[i + 1][j] = wall[i][j];
			for (int i = 0; i < 8; ++i) wall[0][i] = 0;
		}
		if (wall[here.first][here.second])