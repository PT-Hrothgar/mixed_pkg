#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "factors.h"

static PyObject *get_factors(PyObject *self, PyObject *args)
{
    long long num;

    if (!PyArg_ParseTuple(args, "L", &num))
    {
        return NULL;
    }
    if (num < 2)
    {
        PyErr_SetString(PyExc_ValueError, "Number must be >=2");
        return NULL;
    }

    node *factors = factor(num);

    if (factors == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "Out of memory");
        return NULL;
    }

    // Create an empty Python list
    PyObject *result = PyList_New(0);
    if (result == NULL)
    {
        freelist(factors, false, "");
        return NULL;
    }
    node *this_node = factors;
    PyObject *this_factor;

    while (this_node != NULL)
    {
        if ((this_factor = PyLong_FromLong(this_node->num)) == NULL)
        {
            freelist(factors, false, "");
            Py_DECREF(result);
            return NULL;
        }
        if (PyList_Append(result, this_factor) == -1)
        {
            freelist(factors, false, "");
            Py_DECREF(result);
            return NULL;
        }
        this_node = this_node->next;
    }

    freelist(factors, false, "");
    return result;
}

static PyMethodDef module_methods[] = {
    {"get_factors", get_factors, METH_VARARGS, "\
get_factors(num: int, /) -> list[int]\n\n\
Return the prime factors of a given integer, which must be >=2\
"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef primefactors_module = {
    .m_name = "c_helpers",
    .m_methods = module_methods,
    .m_doc = "Mathematical functions for Python with all the speed of C",
    .m_traverse = NULL,
    .m_clear = NULL,
    .m_free = NULL
};

PyMODINIT_FUNC PyInit_c_helpers(void)
{
    PyObject *mod = PyModule_Create(&primefactors_module);
    if (mod == NULL)
    {
        return NULL;
    }
    return mod;
}
