/* define a structure, with the function pointer,
which is just like a class (**cough**, mantained
by ourselved)

for netfilter, how does it do?

could do it tomorrow!! */

/* define the funtion pointer here,
then called in different position */

/* in the netfilter,
 the hook pointer will call the NF_HOOK ,
-> nf_hook_slow -> call in the related position
-> call the funtions defined in the nf_hooks_ops,
which can be registered (injected to)
-> then the function will be called in the right
time.
*/
/** still the relation is not very clear, need fur-
ther study**/

/* thus, for a grader, just hook it to the right
place,
but the grader could be for function, for file and
for folder(module). Thus, just different hook point
at different stages, i.e., when entering folder, en-
tering file, function.

using the hook? does it make it more complicated?
---- answer: no need to follow the rule-chain things,
no need to follow the running logic, just run it, no
need to act like in the routing-forwarding logic.

For simplicity, just run it through for each grader.
but for grader, the trigger point can be used, e.g.,
trigger when every time enter a file, enter a folder...

thus: related structure: folder, file, function should
be defined,

trigged ones will call the right function to update the
grade.

Then where do we store the grade?? just put it in the
tree node (thus, define GRADER_FUN_IN.. things to diff
different kinds of grades)

-- does the target and match resued in the netfilter,
maybe that's why it is registered in a different
double-linked link.
*/

/* thus, need to analyse the netfilter first, too better
 * do this job
 */
