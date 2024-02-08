, tk = 1;
		while (true) {
			if (tq * p[i] > n || tk == k) break;
			ans += query(tree, 1, 0, n, tq * p[i], n) * (k - tk); ans %= MOD;
			tq *= 2LL; ++tk;
		}