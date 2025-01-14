/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF5/releases.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "vol_test.h"
#include "vol_test_util.h"

/*
 * The maximum allowable size of a generated datatype.
 *
 * NOTE: HDF5 currently has limits on the maximum size of
 * a datatype of an object, as this information is stored
 * in the object header. In order to provide maximum
 * compatibility between the native VOL connector and others
 * for this test suite, we limit the size of a datatype here.
 * This value should be adjusted as future HDF5 development
 * allows.
 */
#define GENERATED_DATATYPE_MAX_SIZE 65536

/*
 * The maximum size of a datatype for compact objects that
 * must fit within the size of a native HDF5 object header message.
 * This is typically used for attributes and compact datasets.
 */
#define COMPACT_DATATYPE_MAX_SIZE 1024

/* The maximum level of recursion that the generate_random_datatype()
 * function should go down to, before being forced to choose a base type
 * in order to not cause a stack overflow.
 */
#define TYPE_GEN_RECURSION_MAX_DEPTH 3

/* The maximum number of members allowed in an HDF5 compound type, as
 * generated by the generate_random_datatype() function, for ease of
 * development.
 */
#define COMPOUND_TYPE_MAX_MEMBERS 4

/* The maximum number and size of the dimensions of an HDF5 array
 * datatype, as generated by the generate_random_datatype() function.
 */
#define ARRAY_TYPE_MAX_DIMS 4

/* The maximum number of members and the maximum size of those
 * members' names for an HDF5 enum type, as generated by the
 * generate_random_datatype() function.
 */
#define ENUM_TYPE_MAX_MEMBER_NAME_LENGTH 256
#define ENUM_TYPE_MAX_MEMBERS            16

/* The maximum size of an HDF5 string datatype, as created by the
 * generate_random_datatype() function.
 */
#define STRING_TYPE_MAX_SIZE 1024

/*
 * The maximum dimensionality and dimension size of a dataspace
 * generated for an attribute or compact dataset.
 */
#define COMPACT_SPACE_MAX_DIM_SIZE 4
#define COMPACT_SPACE_MAX_DIMS     3

/*
 * Helper function to generate a random HDF5 datatype in order to thoroughly
 * test the VOL connector's support for datatypes. The parent_class parameter
 * is to support recursive generation of datatypes. In most cases, this
 * function should be called with H5T_NO_CLASS for the parent_class parameter.
 */
/*
 * XXX: limit size of datatype generated
 */
hid_t
generate_random_datatype(H5T_class_t parent_class, hbool_t is_compact)
{
    static int depth      = 0;
    hsize_t   *array_dims = NULL;
    size_t     i;
    hid_t      compound_members[COMPOUND_TYPE_MAX_MEMBERS];
    hid_t      datatype = H5I_INVALID_HID;

    depth++;

    for (i = 0; i < COMPOUND_TYPE_MAX_MEMBERS; i++)
        compound_members[i] = H5I_INVALID_HID;

    switch (rand() % H5T_NCLASSES) {
case_integer:
    case H5T_INTEGER: {
        switch (rand() % 16) {
            case 0:
                if ((datatype = H5Tcopy(H5T_STD_I8BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 1:
                if ((datatype = H5Tcopy(H5T_STD_I8LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 2:
                if ((datatype = H5Tcopy(H5T_STD_I16BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 3:
                if ((datatype = H5Tcopy(H5T_STD_I16LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 4:
                if ((datatype = H5Tcopy(H5T_STD_I32BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 5:
                if ((datatype = H5Tcopy(H5T_STD_I32LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 6:
                if ((datatype = H5Tcopy(H5T_STD_I64BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 7:
                if ((datatype = H5Tcopy(H5T_STD_I64LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 8:
                if ((datatype = H5Tcopy(H5T_STD_U8BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 9:
                if ((datatype = H5Tcopy(H5T_STD_U8LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 10:
                if ((datatype = H5Tcopy(H5T_STD_U16BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 11:
                if ((datatype = H5Tcopy(H5T_STD_U16LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 12:
                if ((datatype = H5Tcopy(H5T_STD_U32BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 13:
                if ((datatype = H5Tcopy(H5T_STD_U32LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 14:
                if ((datatype = H5Tcopy(H5T_STD_U64BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            case 15:
                if ((datatype = H5Tcopy(H5T_STD_U64LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined integer type\n");
                    goto done;
                }

                break;

            default:
                H5_FAILED();
                HDprintf("    invalid value for predefined integer type; should not happen\n");
                goto done;
        }

        break;
    }

case_float:
    case H5T_FLOAT: {
        switch (rand() % 4) {
            case 0:
                if ((datatype = H5Tcopy(H5T_IEEE_F32BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined floating-point type\n");
                    goto done;
                }

                break;

            case 1:
                if ((datatype = H5Tcopy(H5T_IEEE_F32LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined floating-point type\n");
                    goto done;
                }

                break;

            case 2:
                if ((datatype = H5Tcopy(H5T_IEEE_F64BE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined floating-point type\n");
                    goto done;
                }

                break;

            case 3:
                if ((datatype = H5Tcopy(H5T_IEEE_F64LE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't copy predefined floating-point type\n");
                    goto done;
                }

                break;

            default:
                H5_FAILED();
                HDprintf("    invalid value for floating point type; should not happen\n");
                goto done;
        }

        break;
    }

case_time:
    case H5T_TIME: {
        /* Time datatype is unsupported, try again */
        goto reroll;
        break;
    }

case_string:
    case H5T_STRING: {
        /* Note: currently only H5T_CSET_ASCII is supported for the character set and
         * only H5T_STR_NULLTERM is supported for string padding for variable-length
         * strings and only H5T_STR_NULLPAD is supported for string padding for
         * fixed-length strings, but these may change in the future.
         */
        if (0 == (rand() % 2)) {
            if ((datatype = H5Tcreate(H5T_STRING, (size_t)(rand() % STRING_TYPE_MAX_SIZE) + 1)) < 0) {
                H5_FAILED();
                HDprintf("    couldn't create fixed-length string datatype\n");
                goto done;
            }

            if (H5Tset_strpad(datatype, H5T_STR_NULLPAD) < 0) {
                H5_FAILED();
                HDprintf("    couldn't set H5T_STR_NULLPAD for fixed-length string type\n");
                goto done;
            }
        }
        else {
            /*
             * Currently, all VL datatypes are disabled.
             */
            goto reroll;

#if 0
                if ((datatype = H5Tcreate(H5T_STRING, H5T_VARIABLE)) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't create variable-length string datatype\n");
                    goto done;
                }

                if (H5Tset_strpad(datatype, H5T_STR_NULLTERM) < 0) {
                    H5_FAILED();
                    HDprintf("    couldn't set H5T_STR_NULLTERM for variable-length string type\n");
                    goto done;
                }
#endif
        }

        if (H5Tset_cset(datatype, H5T_CSET_ASCII) < 0) {
            H5_FAILED();
            HDprintf("    couldn't set string datatype character set\n");
            goto done;
        }

        break;
    }

case_bitfield:
    case H5T_BITFIELD: {
        /* Bitfield datatype is unsupported, try again */
        goto reroll;
        break;
    }

case_opaque:
    case H5T_OPAQUE: {
        /* Opaque datatype is unsupported, try again */
        goto reroll;
        break;
    }

case_compound:
    case H5T_COMPOUND: {
        size_t num_members;
        size_t next_offset   = 0;
        size_t compound_size = 0;

        /* Currently only allows arrays of integer, float or string. Pick another type if we
         * are creating an array of something other than these. Also don't allow recursion
         * to go too deep. Pick another type that doesn't recursively call this function. */
        if (H5T_ARRAY == parent_class || depth > TYPE_GEN_RECURSION_MAX_DEPTH)
            goto reroll;

        if ((datatype = H5Tcreate(H5T_COMPOUND, 1)) < 0) {
            H5_FAILED();
            HDprintf("    couldn't create compound datatype\n");
            goto done;
        }

        num_members = (size_t)(rand() % COMPOUND_TYPE_MAX_MEMBERS + 1);

        for (i = 0; i < num_members; i++) {
            size_t member_size;
            char   member_name[256];

            HDsnprintf(member_name, 256, "compound_member%zu", i);

            if ((compound_members[i] = generate_random_datatype(H5T_NO_CLASS, is_compact)) < 0) {
                H5_FAILED();
                HDprintf("    couldn't create compound datatype member %zu\n", i);
                goto done;
            }

            if (!(member_size = H5Tget_size(compound_members[i]))) {
                H5_FAILED();
                HDprintf("    couldn't get compound member %zu size\n", i);
                goto done;
            }

            compound_size += member_size;

            if (H5Tset_size(datatype, compound_size) < 0) {
                H5_FAILED();
                HDprintf("    couldn't set size for compound datatype\n");
                goto done;
            }

            if (H5Tinsert(datatype, member_name, next_offset, compound_members[i]) < 0) {
                H5_FAILED();
                HDprintf("    couldn't insert compound datatype member %zu\n", i);
                goto done;
            }

            next_offset += member_size;
        }

        break;
    }

case_reference:
    case H5T_REFERENCE: {
        /* Temporarily disable generation of reference datatypes */
        goto reroll;

        /* Currently only allows arrays of integer, float or string. Pick another type if we
         * are creating an array of something other than these. */
        if (H5T_ARRAY == parent_class)
            goto reroll;

        if (0 == (rand() % 2)) {
            if ((datatype = H5Tcopy(H5T_STD_REF_OBJ)) < 0) {
                H5_FAILED();
                HDprintf("    couldn't copy object reference datatype\n");
                goto done;
            }
        }
        else {
            /* Region references are currently unsupported */
            goto reroll;

            if ((datatype = H5Tcopy(H5T_STD_REF_DSETREG)) < 0) {
                H5_FAILED();
                HDprintf("    couldn't copy region reference datatype\n");
                goto done;
            }
        }

        break;
    }

case_enum:
    case H5T_ENUM: {
        /* Currently doesn't currently support ARRAY of ENUM, so try another type
         * if this happens. */
        if (H5T_ARRAY == parent_class)
            goto reroll;

        if ((datatype = H5Tenum_create(H5T_NATIVE_INT)) < 0) {
            H5_FAILED();
            HDprintf("    couldn't create enum datatype\n");
            goto done;
        }

        for (i = 0; i < (size_t)(rand() % ENUM_TYPE_MAX_MEMBERS + 1); i++) {
            char name[ENUM_TYPE_MAX_MEMBER_NAME_LENGTH];
            int  value = rand();

            HDsnprintf(name, ENUM_TYPE_MAX_MEMBER_NAME_LENGTH, "enum_val%zu", i);

            if (H5Tenum_insert(datatype, name, &value) < 0) {
                H5_FAILED();
                HDprintf("    couldn't insert member into enum datatype\n");
                goto done;
            }
        }

        break;
    }

case_vlen:
    case H5T_VLEN: {
        /* Variable-length datatypes are unsupported, try again */
        goto reroll;
        break;
    }

case_array:
    case H5T_ARRAY: {
        unsigned ndims;
        hid_t    base_datatype = H5I_INVALID_HID;

        /* Currently doesn't currently support ARRAY of ARRAY, so try another type
         * if this happens. Also check for too much recursion. */
        if (H5T_ARRAY == parent_class || depth > TYPE_GEN_RECURSION_MAX_DEPTH)
            goto reroll;

        ndims = (unsigned)(rand() % ARRAY_TYPE_MAX_DIMS + 1);

        if (NULL == (array_dims = (hsize_t *)HDmalloc(ndims * sizeof(*array_dims))))
            goto done;

        for (i = 0; i < ndims; i++)
            array_dims[i] = (hsize_t)(rand() % MAX_DIM_SIZE + 1);

        if ((base_datatype = generate_random_datatype(H5T_ARRAY, is_compact)) < 0) {
            H5_FAILED();
            HDprintf("    couldn't create array base datatype\n");
            goto done;
        }

        if ((datatype = H5Tarray_create2(base_datatype, ndims, array_dims)) < 0) {
            H5_FAILED();
            HDprintf("    couldn't create array datatype\n");
            goto done;
        }

        break;
    }

    default:
        H5_FAILED();
        HDprintf("    invalid datatype class\n");
        break;
    } /* end if */

done:
    if (depth > 0)
        depth--;

    if (datatype < 0) {
        for (i = 0; i < COMPOUND_TYPE_MAX_MEMBERS; i++) {
            if (compound_members[i] > 0 && H5Tclose(compound_members[i]) < 0) {
                H5_FAILED();
                HDprintf("    couldn't close compound member %zu\n", i);
            }
        }
    }

    if (array_dims) {
        HDfree(array_dims);
        array_dims = NULL;
    }

    if (is_compact && (depth == 0)) {
        size_t type_size;

        /*
         * Check to make sure that the generated datatype does
         * not exceed the maximum compact datatype size if a
         * compact datatype was requested.
         */
        if (0 == (type_size = H5Tget_size(datatype))) {
            H5_FAILED();
            HDprintf("    failed to retrieve datatype's size\n");
            H5Tclose(datatype);
            datatype = H5I_INVALID_HID;
        }
        else {
            if (type_size > COMPACT_DATATYPE_MAX_SIZE) {
                /*
                 * Generate a new datatype.
                 */
                H5Tclose(datatype);
                datatype = H5I_INVALID_HID;
                goto reroll;
            }
        }
    }

    return datatype;

reroll:
    if (depth > 0)
        depth--;

    /*
     * The datatype generation resulted in a datatype that is currently invalid
     * for these tests, try again.
     */
    switch (rand() % H5T_NCLASSES) {
        case H5T_INTEGER:
            goto case_integer;
        case H5T_FLOAT:
            goto case_float;
        case H5T_TIME:
            goto case_time;
        case H5T_STRING:
            goto case_string;
        case H5T_BITFIELD:
            goto case_bitfield;
        case H5T_OPAQUE:
            goto case_opaque;
        case H5T_COMPOUND:
            goto case_compound;
        case H5T_REFERENCE:
            goto case_reference;
        case H5T_ENUM:
            goto case_enum;
        case H5T_VLEN:
            goto case_vlen;
        case H5T_ARRAY:
            goto case_array;
        default:
            H5_FAILED();
            HDprintf("    invalid value for goto\n");
            break;
    }

    return H5I_INVALID_HID;
}

/*
 * Helper function to generate a random HDF5 dataspace in order to thoroughly
 * test the VOL connector's support for dataspaces.
 */
hid_t
generate_random_dataspace(int rank, const hsize_t *max_dims, hsize_t *dims_out, hbool_t is_compact)
{
    hsize_t dataspace_dims[H5S_MAX_RANK];
    size_t  i;
    hid_t   dataspace_id = H5I_INVALID_HID;

    if (rank < 0)
        TEST_ERROR
    if (is_compact && (rank > COMPACT_SPACE_MAX_DIMS)) {
        HDprintf("    current rank of compact dataspace (%lld) exceeds maximum dimensionality (%lld)\n",
                 (long long)rank, (long long)COMPACT_SPACE_MAX_DIMS);
        TEST_ERROR
    }

    /*
     * XXX: if max_dims is specified, make sure that the dimensions generated
     * are not larger than this.
     */
    for (i = 0; i < (size_t)rank; i++) {
        if (is_compact)
            dataspace_dims[i] = (hsize_t)(rand() % COMPACT_SPACE_MAX_DIM_SIZE + 1);
        else
            dataspace_dims[i] = (hsize_t)(rand() % MAX_DIM_SIZE + 1);

        if (dims_out)
            dims_out[i] = dataspace_dims[i];
    }

    if ((dataspace_id = H5Screate_simple(rank, dataspace_dims, max_dims)) < 0)
        TEST_ERROR

    return dataspace_id;

error:
    return H5I_INVALID_HID;
}

int
create_test_container(char *filename)
{
    hid_t file_id = H5I_INVALID_HID;
#ifdef GROUP_CREATION_IS_SUPPORTED
    hid_t group_id = H5I_INVALID_HID;
#endif

    if ((file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT)) < 0) {
        HDprintf("    couldn't create testing container file '%s'\n", filename);
        goto error;
    }

#ifdef GROUP_CREATION_IS_SUPPORTED
    /* Create container groups for each of the test interfaces
     * (group, attribute, dataset, etc.).
     */
    if ((group_id = H5Gcreate2(file_id, GROUP_TEST_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) >= 0) {
        HDprintf("    created container group for Group tests\n");
        H5Gclose(group_id);
    }

    if ((group_id = H5Gcreate2(file_id, ATTRIBUTE_TEST_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) >=
        0) {
        HDprintf("    created container group for Attribute tests\n");
        H5Gclose(group_id);
    }

    if ((group_id = H5Gcreate2(file_id, DATASET_TEST_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) >=
        0) {
        HDprintf("    created container group for Dataset tests\n");
        H5Gclose(group_id);
    }

    if ((group_id = H5Gcreate2(file_id, DATATYPE_TEST_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) >=
        0) {
        HDprintf("    created container group for Datatype tests\n");
        H5Gclose(group_id);
    }

    if ((group_id = H5Gcreate2(file_id, LINK_TEST_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) >= 0) {
        HDprintf("    created container group for Link tests\n");
        H5Gclose(group_id);
    }

    if ((group_id = H5Gcreate2(file_id, OBJECT_TEST_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) >=
        0) {
        HDprintf("    created container group for Object tests\n");
        H5Gclose(group_id);
    }

    if ((group_id = H5Gcreate2(file_id, MISCELLANEOUS_TEST_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT,
                               H5P_DEFAULT)) >= 0) {
        HDprintf("    created container group for Miscellaneous tests\n");
        H5Gclose(group_id);
    }
#endif

    if (H5Fclose(file_id) < 0) {
        HDprintf("    failed to close testing container\n");
        goto error;
    }

    return 0;

error:
    H5E_BEGIN_TRY
    {
#ifdef GROUP_CREATION_IS_SUPPORTED
        H5Gclose(group_id);
#endif
        H5Fclose(file_id);
    }
    H5E_END_TRY;

    return -1;
}
