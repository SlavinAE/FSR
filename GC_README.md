Попробем алгоритм "жадная раскраска" - первую вершину красим в цвет 1, для остальных смотрим на цвета их соседей и красим
в цвет, который не встречался (пусть в наименьший). Размуеется, результат работы сильно зависит от порядка рассмотрения вершин,
но точно существует порядок, приводящий нас к оптимальному ответу. Поэтому посмотрим, что получится. Если что, поиграемся с
порядком рассмотрения