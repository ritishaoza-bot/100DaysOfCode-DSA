/*Given head, the head of a linked list, determine if the linked list has a cycle in it.
There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.
Return true if there is a cycle in the linked list. Otherwise, return false.
 
Example 1:
Input: head = [3,2,0,-4], pos = 1Output: trueExplanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
Example 2:
Input: head = [1,2], pos = 0Output: trueExplanation: There is a cycle in the linked list, where the tail connects to the 0th node.
Example 3:
Input: head = [1], pos = -1Output: falseExplanation: There is no cycle in the linked list.
 
Constraints:
The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list. */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

int main() {
    struct ListNode *n1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *n2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    
    n1->val = 1;
    n1->next = n2;
    n2->val = 2;
    n2->next = n1; 

    if (hasCycle(n1)) {
        printf("Cycle detected\n");
    } else {
        printf("No cycle\n");
    }

    free(n1);
    free(n2);
    return 0;
}