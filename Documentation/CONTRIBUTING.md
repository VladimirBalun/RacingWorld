# Contributing to RacingWorld

Following these guidelines helps to communicate that you respect the time of the
developers managing and developing this open source project. In return, they should
reciprocate that respect in addressing your issue or assessing patches and features.

## Pull requests

Please ask first before embarking on any significant pull request, otherwise you
risk spending a lot of time working on something that the project's developers
might not want to merge into the project.

Adhering to the following process is the best way to get your work included in the project:

1.  Fork the project, clone your fork, and configure the remotes:

        git clone https://github.com/<your-username>/RacingWorld.git
        cd RacingWorld
        git remote add upstream https://github.com/twbs/RacingWorld.git

2.  If you cloned a while ago, get the latest changes from upstream:

        git checkout develop
        git pull --rebase upstream develop

3.  Create a new topic branch (off the main project development branch) to contain your feature, change, or fix:

        git checkout -b <topic-branch-name>

4.  Commit your changes in logical chunks(but before commit read our
 <a href="./COMMITS.md">commits style guide</a>). Use Git's interactive rebase 
 feature to tidy up your commits before making them public.

5.  Locally rebase the upstream development branch into your topic branch:

        git pull --rebase upstream develop

6.  Push your topic branch up to your fork:

        git push origin <topic-branch-name>

7.  Open a Pull Request with a clear title and description against the develop branch.               

## Feature requests

Before opening a feature request, please take a moment to find out whether your
idea fits with the scope and aims of the project. It's up to you to make a strong
case to convince the project's developers of the merits of this feature. Please
provide as much detail and context as possible.

## Bug reports

A bug is a demonstrable problem that is caused by the code in the repository. Good bug reports are extremely helpful, so thanks!
A good bug report shouldn't leave others needing to chase you up for more information. Please try to be as detailed as possible in your report. What is your environment? What steps will reproduce the issue? What would you expect to be the outcome? All these details will help people to fix any potential bugs.

Example:

> Short and descriptive example bug report title
>
>  A summary of the issue and the OS environment in which it occurs. If suitable, include the steps required to reproduce the bug.
>
>  This is the first step
>  This is the second step
>  Further steps, etc.
>
>   Any other information you want to share that is relevant to the issue being reported. This might include the lines of code that you have   identified as causing the bug, and potential solutions (and your opinions on their merits).

---

If you have any questions, please contact: vladimirbalun@yandex.ru
