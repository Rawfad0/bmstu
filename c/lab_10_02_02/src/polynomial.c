#include "polynomial.h"

void free_term(term_t *term)
{
    free(term);
}

void free_polynomial_list(node_t **head)
{
    while (*head != NULL)
        free(pop_front(head));
}

int compare_by_power(const void *p, const void *q)
{
    return - ((term_t *) p)->power + ((term_t *) q)->power;
}

term_t *make_term(int coef, int pow)
{
    term_t *term = malloc(sizeof(term_t));
    if (term != NULL)
    {
        term->coefficient = coef;
        term->power = pow;
    }
    return term;
}

int insert_term(node_t **pol, int coef, int pow)
{
    int rc = RC_OK;
    term_t *term = NULL;
    node_t *node = NULL;
    if ((term = make_term(coef, pow)) == NULL)
        rc = RC_ALLOCATION_FAILED;
    else if ((node = make_node(term)) == NULL)
        free_term(term), rc = RC_ALLOCATION_FAILED;
    else
        push_front(pol, node);
    return rc;
}

int read_polynomial_list(node_t **polynomial)
{
    int rc = RC_OK;
    size_t n = 0;
    int coefficient = 0;
    if (scanf("%zu", &n) != 1)
        rc = RC_INCORRECT_INPUT;
    for (size_t i = 0; i < n && rc == RC_OK; i++)
        if (scanf("%d", &coefficient) != 1)
            rc = RC_INCORRECT_INPUT; 
        else
            rc = insert_term(polynomial, coefficient, n - i - 1);
    if (rc == RC_OK)
        *polynomial = reverse(*polynomial);
    return rc;
}

void print_polynomial_list(node_t *polynomial)
{
    term_t *term = NULL;
    if (polynomial == NULL)
        printf("0 0 ");
    for (node_t *node = polynomial; node != NULL; node = next_node(node))
    {
        term = get_data(node);
        printf("%d ", term->coefficient);
    }
    printf("L\n");
}

int read_variable_value(int *value)
{
    int rc = RC_OK;
    if (scanf("%d", value) != 1)
        rc = RC_INCORRECT_INPUT;
    return rc;
}

void print_result(int value)
{
    printf("%d\n", value);
}

int calculate(node_t *polynomial, int x)
{
    int res = 0;
    term_t *term = NULL;
    for (node_t *node = polynomial; node != NULL; node = next_node(node))
    {
        term = get_data(node);
        res += term->coefficient * pow(x, term->power);
    }
    return res;
}

void derivative(node_t **polynomial)
{
    term_t *term = NULL;
    node_t *next = NULL;
    for (node_t *node = *polynomial; node != NULL; node = next)
    {
        next = next_node(node);
        term = get_data(node);
        if (term->power == 0)
            free_term(pop_node(polynomial, node));
        else
        {
            term->coefficient *= term->power;
            term->power--;
        }
    }
}

void term_coef_sum(node_t *node1, node_t *node2)
{
    term_t *term1 = get_data(node1);
    term_t *term2 = get_data(node2);

    term1->coefficient += term2->coefficient;
    term2->coefficient = 0;
}

node_t *add(node_t **pol1, node_t **pol2)
{
    node_t *res = sorted_merge(pol1, pol2, compare_by_power);
    node_t *next = NULL;
    for (node_t *node = res; node != NULL && next_node(node) != NULL; node = next)
    {
        next = next_node(node);
        if (compare_by_power(get_data(node), get_data(next)) == 0)
        {
            term_coef_sum(node, next);
            free_term(pop_after(node));
            next = next_node(node);
            if (((term_t *) get_data(node))->coefficient == 0)
                free_term(pop_node(&res, node));
        }
    }
    return res;
}

void divide(node_t **polynomial_src, node_t **polynomial1, node_t **polynomial2)
{
    node_t *next = NULL;
    for (node_t *node = *polynomial_src; node != NULL; node = next)
    {
        next = next_node(node);
        if (((term_t *) get_data(node))->power % 2 == 0)
            push_front(polynomial1, node);
        else
            push_front(polynomial2, node);
    }
    *polynomial1 = reverse(*polynomial1);
    *polynomial2 = reverse(*polynomial2);
    *polynomial_src = NULL;
}
