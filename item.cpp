#include "item.h"

Item::Item(int no, string id, string title, string url) : v_no(no),
    v_id(id),
    v_title(title),
    v_url(url)
{
}

int Item::getNo()
{
    return v_no;
}

string Item::getId()
{
    return v_id;
}

string Item::getTitle()
{
    return v_title;
}

string Item::getUrl()
{
    return v_url;
}
