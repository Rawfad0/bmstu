/**
 * @file list.h
 * @brief Модуль содержащий связный список и функции работы со связным списком
 * 
 */

#ifndef __LIST__H__
#define __LIST__H__

#include <stddef.h>
#include <stdlib.h>

// Тип структуры односвязного списка
typedef struct node node_t;

// Базовые функции со списком
node_t *make_node(void *data);

void *get_data(node_t *head);

node_t *next_node(node_t *head);

// Задачи на работу с одним элементом списка
void *pop_front(node_t **head);

void *pop_back(node_t **head);

void insert(node_t **head, node_t *elem, node_t *before);

// Задача на работу с целым списком
node_t *reverse(node_t *head);

// Задача на сортировку
void front_back_split(node_t *head, node_t **back);

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif
