/*********************************
 * Reviewer:   
 * Author: Sigal Tal		
 * File: sorted_list.h
 * ******************************/
#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include "sorted_list.h"
#include "dll.h"

struct sorted_list
{
    dll_t *dlist;
    sorted_list_compare_func_t compare_func;
    void *user_param;
};

sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare_func, void *user_param)
{
    sorted_list_t *list=NULL;
    assert(compare_func);

    list=(sorted_list_t *)malloc(sizeof(sorted_list_t));
    if(!list)
    {
        return NULL;
    }

    list->dlist=DListCreate();
    if(!list->dlist)
    {
        free(list);
        list=NULL;
        return NULL;
    }

    list->compare_func=compare_func;
    list->user_param=user_param;

    return list;
}

void SortedListDestroy(sorted_list_t *list)
{
    assert(list);

    DListDestroy(list->dlist);
    list->dlist=NULL;
    free(list);
    list=NULL;
}

sorted_list_iterator_t SortedListIterInit(void)
{
    sorted_list_iterator_t iter;
    iter.dll_iter=NULL;

    #ifndef NDEBUG
    iter.sorted_list=NULL;
    #endif

    return iter;
}

sorted_list_iterator_t SortedListBegin(const sorted_list_t *list)
{
    sorted_list_iterator_t iter=SortedListIterInit();

    assert(list);

    iter.dll_iter=DListBegin(list->dlist);

    #ifndef NDEBUG
    iter.sorted_list=(sorted_list_t *)list;
    #endif

    return iter;
}

sorted_list_iterator_t SortedListEnd(const sorted_list_t *list)
{
    sorted_list_iterator_t iter=SortedListIterInit();

    assert(list);

    iter.dll_iter=DListEnd(list->dlist);

    #ifndef NDEBUG
    iter.sorted_list=(sorted_list_t *)list;
    #endif

    return iter;
}


sorted_list_iterator_t SortedListNext(sorted_list_iterator_t iter)
{
    iter.dll_iter=DListNext(iter.dll_iter);

    return iter;
}


sorted_list_iterator_t SortedListPrev(sorted_list_iterator_t iter)
{
    iter.dll_iter=DListPrev(iter.dll_iter);

    return iter;
}

void *SortedListGetData(sorted_list_iterator_t iter)
{
    return DListGetData(iter.dll_iter);
}

int SortedListIsSameIter(sorted_list_iterator_t iter1, sorted_list_iterator_t iter2)
{
    return DListIsSameIter(iter1.dll_iter, iter2.dll_iter);
}

size_t SortedListSize(const sorted_list_t *list)
{
    assert(list);

    return DListSize(list->dlist);
}

int SortedListIsEmpty(const sorted_list_t *list)
{
    assert(list);

    return DListIsEmpty(list->dlist);
}


sorted_list_iterator_t SortedListInsert(sorted_list_t *list, void *data)
{
    sorted_list_iterator_t insert_place=SortedListIterInit();

    assert(list);
    assert(data);

    insert_place=SortedListFind(list,SortedListBegin(list),SortedListEnd(list),data);

    insert_place.dll_iter=DListInsert(list->dlist,insert_place.dll_iter,data);

    #ifndef NDEBUG
    insert_place.sorted_list=list;
    #endif

    return insert_place;
}

sorted_list_iterator_t SortedListFind(
                                        sorted_list_t *list,
                                        sorted_list_iterator_t from, 
                                        sorted_list_iterator_t to, 
                                        const void *data)
{
    assert(list);
    assert(data);
    assert(from.sorted_list==to.sorted_list);

    while(!SortedListIsSameIter(from, to) && 
            (list->compare_func(SortedListGetData(from),data,list->user_param)>=0))
    {
        from=SortedListNext(from);
    }

    return from;
}

sorted_list_iterator_t SortedListRemove(sorted_list_iterator_t curr)
{
    curr.dll_iter=DListRemove(curr.dll_iter);

    return curr;
}

void *SortedListPopFront(sorted_list_t *list)
{
    assert(list);

    return DListPopFront(list->dlist);;
} 

void *SortedListPopBack(sorted_list_t *list)
{
    assert(list);

    return DListPopBack(list -> dlist);
}

int SortedListForEach(
                        sorted_list_iterator_t from, 
                        sorted_list_iterator_t to, 
                        void *param, 
                        sorted_list_action_func_t action_func)
{
    assert(param);
    assert(action_func);
    assert(from.sorted_list==to.sorted_list);

    return DListForEach(from.dll_iter, to.dll_iter, param, action_func);
}

sorted_list_iterator_t SortedListFindIf(
                                        sorted_list_iterator_t from, 
                                        sorted_list_iterator_t to, 
                                        const void *data, 
                                        sorted_list_is_match_func_t is_match_func)
{
    assert(data);
    assert(from.sorted_list==to.sorted_list);

    /*while(!SortedListIsSameIter(from, to) && 
            !(is_match_func(SortedListGetData(from),data)))
    {
        from=SortedListNext(from);
    }*/
    from.dll_iter=DListFind(from.dll_iter, to.dll_iter, data, is_match_func);

    return from;
}

void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
    sorted_list_iterator_t place_in_dest=SortedListBegin(dest_list);
    sorted_list_iterator_t place_in_src=SortedListBegin(src_list);
    sorted_list_iterator_t new_begin_src=SortedListBegin(src_list);


    while(!SortedListIsSameIter(new_begin_src,SortedListEnd(src_list)))
    {
        place_in_dest=SortedListFind(
                                        dest_list, 
                                        place_in_dest, 
                                        SortedListEnd(dest_list), 
                                        SortedListGetData(place_in_src));

        if(SortedListIsSameIter(place_in_dest,SortedListEnd(dest_list)))
        {
            place_in_dest.dll_iter=DListSplice(
                                                place_in_dest.dll_iter,
                                                new_begin_src.dll_iter, 
                                                SortedListEnd(src_list).dll_iter);
            break;
        }

        place_in_src=SortedListFind(
                                    src_list, 
                                    new_begin_src, 
                                    SortedListEnd(src_list), 
                                    SortedListGetData(place_in_dest));

        place_in_dest.dll_iter=DListSplice(
                                            place_in_dest.dll_iter,
                                            new_begin_src.dll_iter, 
                                            place_in_src.dll_iter);
        new_begin_src=place_in_src;
    }

}