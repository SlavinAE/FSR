	Идея:
1. соберем путь по порядку вхождения вершин в вектор Data
2. выкинем три самых тяжелых ребра
   	   проблема: искать их перебором - O(n) доп. времени, О(1) по памяти / хранить длины ребер
	             вместе с вершинами - поиск О(1) по времени, О(n) по памяти. С другой стороны можно
		     подвязать иерархическую структуру данных - будет pog
3. если хранить веса ребер, инцидентных вершинам, то легко понять какие есть способы дозамкнуть множество
   ребер до гамильтонова пути. Достроим граф, минимизируя сумму новых длин
4. если на шаге 3 общая длина пути изменилась - повторить
   если не изменилась - попробовать выкинуть 4, 5 и 6 по длине ребра и повторить.

Пахнет рекурсией, каждый раз искать k-ые статистики становится совсем не весело. Точно вспомнить структуры
данных, освежить в памяти алгоритмы
______________________________________________________________________________________________________________________________________

Заведем vector<int> numOfIncEdges(path.size, 2) - число инцидентных ребер для каждой вершины. Изначально оно равно 2.
Запомним текущую длину пути

1. Удалим 3 первых ребра из path, сделаем -- в numOfIncEdges[i], если i-тая вершина образует удаляемое ребро. Тогда значение в вектор
стнает равным либо 1, либо 2.
2. Среди всех вершин, для которых numOfIncEdges не равно 2, перебором найдем наименьшее ребро. Повторим еще два раза.
3. Удалим следующие 3 ребра, добавим найденные в пункте 2 три ребра. Тогда мы минимизировали 1, 2 и 3 статистики, собираемся
минимизировать 4,5 и 6 статистики.
4. Будем повторять, пока не дойдем до конца. Если число ребер не кратно трем, в последний раз возьмем последние три ребра с конца(try-catch)
5. Если длина пути уменьшилась - повторим. Если нет - получен ответ.

(РЕАЛИЗОВАНО В TSP_VER1.CPP)
____________________________________________________________________________
обсудили с Андреем несколько эвристик, попробовать что-то из
	 добавляем вершину в очередь минимизируя сумму расстояний до соседей  (РЕАЛИЗОВАНО В TSP_VER2.CPP)



	 стартуем из n вершин, собирая свои цепи (~ построение остовного дерева)