# Undo Mistakes 😱

## git restore filename
- will discard uncommited change for this file
- cannot be undone afterward

### git restore -p filename
- p stands for patches
- will als for each change in this file to be restore or not

### git restore .
- undo all changes since last commit


## git commit --ammend -m "Commit Message"
- change commit message of last commit
- do not change already pushed commit

## git revert hash_value
- it reverts specified single commit
- hash_value can be seen through `git log`, eg. 74e3b2b
- it makes new commit by exactly doing opposite changes, so it is very safe

## git reset --hard 74e3b2b
- it resets HEAD to certain commit in history while deleting all the commits after it
- if commits just local then they are gone forever

### git reset --mixed 74e3b2b
- same as previous one but it will store all the changes from the removed commits as uncommited changes

## git restore --source 74e3b2b filename
- will restore this file to certain commit (just 1 file)

## git reflog
- it is advance version of `git log`

### Restore after hard reset
- it even stores history for certain time after `git reset --hard`
- you can `git reset 74e3b2b` but creating mew branch is preferred by `git branch branch_name 74e3b2b`

### Restore after deleting entire branch
- look for hash_value from `git reflog`
- then `git branch branch_name 36a46a1`

## Moving commit to another branch
- if you want to *move* cirtain commits from current branch to new branch
    ```
    git branch new_branch_name
    git reset HEAD~1 --hard
    ```
- if moving commit to already present branch
    ```
    git checkout branch_name
    git cherry-pick 36a46a1
    git checkout previous_branch_name
    git reset --hard HEAD~1
    ```
## Interactive rebase
- is very advance, *dangerous* and powerful tool
- read comments during the process

### Change commit history
- for example if you want to change commit history upto 3 commits before current HEAD
- `git rebase -i HEAD~3`
- you can change/*reword* commit messages, delete/*drop* commits, *squash* multiple commits together


