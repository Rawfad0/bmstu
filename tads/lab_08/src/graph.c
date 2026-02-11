#include "graph.h"

#include <stdint.h>

struct graph
{
    matrix_t matrix;
};

graph_t graph_init(void)
{
    graph_t graph = malloc(sizeof(struct graph));
    if (graph != NULL)
    {
        graph->matrix.matrix = NULL;
        graph->matrix.n = 0;
        graph->matrix.m = 0;
    }
    return graph;
}

int graph_read(char **filename, graph_t *graph)
{
    graph_del(graph);
    *graph = graph_init();
    free(*filename), *filename = NULL;
    
    int rc = RC_OK;
    char *filepath = NULL;
    printf("Введите путь к файлу с данными (например: 'data/10'):\n");
    if ((rc = get_input(&filepath, stdin)) != RC_OK)
        return rc;

    if ((rc = read_matrix(filepath, &(*graph)->matrix)) != RC_OK)
        return rc;
    
    // for (size_t i = 0; i < (*graph)->matrix.n; i++)
    //     for (size_t j = 0; j < (*graph)->matrix.n; j++)
    //         if (i != j && (*graph)->matrix.matrix[i][j] == 0)
    //             (*graph)->matrix.matrix[i][j] = SIZE_MAX;
    *filename = filepath, printf("Файл успешно прочитан.\n");
    return rc;
}

int graph_write(graph_t graph)
{
    int rc = RC_OK;
    FILE *f = fopen("res.dot", "w");
    if (!f)
        rc = RC_INCORRECT_FILE;
    else
    {
        fprintf(f, "graph n3 {\n");
        for (size_t i = 0; i < graph->matrix.n; i++)
            for (size_t j = i + 1; j < graph->matrix.n; j++)
                if (graph->matrix.matrix[i][j] != 0)
                    fprintf(f, "%zu -- %zu [label = %zu];\n", i, j, graph->matrix.matrix[i][j]);
        fprintf(f, "}\n");
    }
    if (f)
        fclose(f);
    return rc;
}

size_t find_min(size_t n, size_t dist[], size_t vis[])
{
    size_t min = SIZE_MAX, min_i = 0;
    for (size_t i = 0; i < n; i++)
        if (dist[i] <= min && vis[i] == 0)
            min = dist[i], min_i = i;
    return min_i;
}

// Алгоритм Дейкстры
void dijkstra(graph_t graph, size_t src)
{
    size_t n = graph->matrix.n;
    size_t *dist = malloc(n * sizeof(size_t));
    // Массив посещения
    size_t *vis = malloc(n * sizeof(size_t));
    
    // Инициализация массива расстояний расстояний от искомой до остальных
    for (size_t i = 0; i < n; i++)
        dist[i] = SIZE_MAX, vis[i] = 0;
    dist[src] = 0;

    for (size_t i = 0; i < n; i++)
    {
        size_t picked = find_min(n, dist, vis); // Нахождение ближайшей
        vis[picked] = 1;                        // Отметка о посещении
        // Минимальные пути от выбранной (помеченной вершины) до соседних 
        // и обновление массива расстояний от искомой
        for (size_t j = 0; j < n; j++)
            if (!vis[j] && graph->matrix.matrix[picked][j] && dist[picked] != SIZE_MAX 
            && dist[picked] + graph->matrix.matrix[picked][j] < dist[j])
                dist[j] = dist[picked] + graph->matrix.matrix[picked][j];
    }
    // Запись результатов
    for (size_t i = 0; i < n; i++)
        graph->matrix.matrix[i][src] = dist[i], graph->matrix.matrix[src][i] = dist[i];
}

// Алгоритм Дейкстры для всех вершин
void dijkstra4all(graph_t graph)
{
    for (size_t i = 0; i < graph->matrix.n; i++)
        dijkstra(graph, i);
}

void d_wrapper(graph_t graph)
{
    if (graph == NULL)
        return;

    double time = 0;
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    dijkstra4all(graph);
    gettimeofday(&te, NULL);
    time = te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;

    size_t sum = 0;
    size_t min_i = 0;
    size_t min_sum;
    for (size_t i = 0; i < graph->matrix.n; i++)
    {
        sum = 0;
        for (size_t j = 0; j < graph->matrix.n; j++)
            sum += graph->matrix.matrix[i][j];
        if (i == 0)
            min_sum = sum;
        else if (sum < min_sum)
            min_sum = sum, min_i = i;
    }
    for (size_t i = 0; i < graph->matrix.n; i++)
    {
        sum = 0;
        for (size_t j = 0; j < graph->matrix.n; j++)
            sum += graph->matrix.matrix[i][j];
        if (i == min_i)
        {
            printf("Сумма (наименьшая) от %zu вершины = %zu:", i, sum);
            for (size_t j = 0; j < graph->matrix.n; j++)
                printf(" %zu", graph->matrix.matrix[i][j]);
            printf("\n");
        }
        else
            printf("Сумма от %zu вершины = %zu\n", i, sum);
    }

    printf("Алгоритм Дейкстры работает за время: %lf секунд\n", time);
}


void floyd_warshall(graph_t graph)
{
    size_t n = graph->matrix.n; // Количество вершин
    // Обход N раз
    for(size_t k = 0; k < n; k++)
        for(size_t i = 0; i < n; i++)
            for(size_t j = i + 1; j < n; j++)
                if (graph->matrix.matrix[i][k] && graph->matrix.matrix[k][j])
                    if (graph->matrix.matrix[i][j] == 0 || graph->matrix.matrix[i][k] + graph->matrix.matrix[k][j] < graph->matrix.matrix[i][j])
                        graph->matrix.matrix[j][i] = (graph->matrix.matrix[i][j] = graph->matrix.matrix[i][k] + graph->matrix.matrix[k][j]); // Если другой путь короче исходного
}

void fw_wrapper(graph_t graph)
{
    if (graph == NULL)
        return;

    double time = 0;
    struct timeval tb, te;

    gettimeofday(&tb, NULL);
    floyd_warshall(graph);
    gettimeofday(&te, NULL);
    time = te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
    
    size_t sum = 0;
    size_t min_i = 0;
    size_t min_sum;
    for (size_t i = 0; i < graph->matrix.n; i++)
    {
        sum = 0;
        for (size_t j = 0; j < graph->matrix.n; j++)
            sum += graph->matrix.matrix[i][j];
        if (i == 0)
            min_sum = sum;
        else if (sum < min_sum)
            min_sum = sum, min_i = i;
    }
    for (size_t i = 0; i < graph->matrix.n; i++)
    {
        sum = 0;
        for (size_t j = 0; j < graph->matrix.n; j++)
            sum += graph->matrix.matrix[i][j];
        if (i == min_i)
        {
            printf("Сумма (наименьшая) от %zu вершины = %zu:", i, sum);
            for (size_t j = 0; j < graph->matrix.n; j++)
                printf(" %zu", graph->matrix.matrix[i][j]);
            printf("\n");
        }
        else
            printf("Сумма от %zu вершины = %zu\n", i, sum);
    }

    printf("Алгоритм Флойда-Уоршелла работает за время: %lf секунд\n", time);
}

void graph_del(graph_t *graph)
{
    if (graph == NULL);
    else if (*graph == NULL);
    else
        free(*graph), *graph = NULL;
}
