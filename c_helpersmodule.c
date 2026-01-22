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
    // Get the list's `append` method
    PyObject *append = PyObject_GetAttrString(result, "append");
    // Arguments to pass to `append`
    PyObject *append_args;
    // Next node in `factors`
    node *next;

    while (factors != NULL)
    {
        // Create a Python tuple containing the factor
        append_args = Py_BuildValue("(L)", factors->num);
        // NULL == no keyword arguments
        PyObject_Call(append, append_args, NULL);
        Py_DECREF(append_args);

        next = factors->next;
        free(factors);
        factors = next;
    }
    Py_DECREF(append);
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
