Iterator insert(const Iterator &pos, const Data &value)
{
    if (pos.current_node != nullptr)
    {
        node_ptr newNode = std::make_unique<Node>(value);
        newNode->next = std::move(pos.current_node->next);
        if (pos.previous_node == nullptr)
        {
            head = std::move(newNode);
            size++;
            return Iterator(head);
        }
        else
        {
            pos.previous_node->next = std::move(newNode);
            size++;
            return Iterator(pos.previous_node->next);
        }
    }
    return pos;
};