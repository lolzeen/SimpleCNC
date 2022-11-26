#include "DisplayWindow.hpp"

DisplayWindow::DisplayWindow(dispWindPtr& ptr1, dispWindPtr& ptr2, dispWindPtr& ptr3, dispWindPtr& ptr4) : next(ptr1), previous(ptr2), inner(ptr3), outter(ptr4) {};
DisplayWindow::DisplayWindow(dispWindPtr& ptr1, uint8_t ptr_id1, dispWindPtr& ptr2, uint8_t ptr_id2, dispWindPtr& ptr3, uint8_t ptr_id3) {
    switch (ptr_id1)
    {
    case NEXT_PTR:
        next = ptr1;
        break;
    case PREV_PTR:
        previous = ptr1;
        break;
    case INNE_PTR:
        inner = ptr1;
        break;
    case OUTT_PTR:
        outter = ptr1;
        break;
    default:
        break;
    }
    switch (ptr_id2)
    {
    case NEXT_PTR:
        next = ptr2;
        break;
    case PREV_PTR:
        previous = ptr2;
        break;
    case INNE_PTR:
        inner = ptr2;
        break;
    case OUTT_PTR:
        outter = ptr2;
        break;
    default:
        break;
    }
    switch (ptr_id3)
    {
    case NEXT_PTR:
        next = ptr3;
        break;
    case PREV_PTR:
        previous = ptr3;
        break;
    case INNE_PTR:
        inner = ptr3;
        break;
    case OUTT_PTR:
        outter = ptr3;
        break;
    default:
        break;
    }
}
DisplayWindow::DisplayWindow(dispWindPtr& ptr1, uint8_t ptr_id1, dispWindPtr& ptr2, uint8_t ptr_id2) {
    switch (ptr_id1)
    {
    case NEXT_PTR:
        next = ptr1;
        break;
    case PREV_PTR:
        previous = ptr1;
        break;
    case INNE_PTR:
        inner = ptr1;
        break;
    case OUTT_PTR:
        outter = ptr1;
        break;
    default:
        break;
    }
    switch (ptr_id2)
    {
    case NEXT_PTR:
        next = ptr2;
        break;
    case PREV_PTR:
        previous = ptr2;
        break;
    case INNE_PTR:
        inner = ptr2;
        break;
    case OUTT_PTR:
        outter = ptr2;
        break;
    default:
        break;
    }
}
DisplayWindow::DisplayWindow(dispWindPtr& ptr, uint8_t ptr_id) {
    switch (ptr_id)
    {
    case NEXT_PTR:
        next = ptr;
        break;
    case PREV_PTR:
        previous = ptr;
        break;
    case INNE_PTR:
        inner = ptr;
        break;
    case OUTT_PTR:
        outter = ptr;
        break;
    default:
        break;
    }
}