# Commits style convention

Our style is to create commits almost fully complies with the 
<a href="https://www.conventionalcommits.org/en/v1.0.0-beta.3/">The Conventional Commits.</a>
But there are also some specific changes, so please read this 
document to the end.

## Commit structure

The commit message should be structured as follows:

---

    <type>(optional scope): <description>

    <optional body>

    <optional footer>

---

*   In the body of a commit we write what has been changed and why.

*   We use the following types of commits:

| Commit type | Description                                                | 
|:-----------:|:----------------------------------------------------------:|
| build       | build of the project or change external dependencies       |
| ci          |  configuring of CI and working with scripts                |
| docs        |  documentation updating                                    |
| feat        | adding new functionality                                   |
| fix         | bug fix                                                    |
| perf        | changes to improve performance                             |
| refactor    | edit code without correcting errors or adding new features |
| revert      | rollback to previous commits                               |
| style       | code style edits(tabs, indents, full stops, commas, etc.)  |
| test        | adding tests                                               |

*   We write the description in the imperative mood, just like Git itself.


    Merge branch 'fix/SECRETMRKT-749-fix-typos-in-titles'
    
*   The description consists only of lowercase letters and we do not download the description of 
the commit with punctuation marks.    

## Commit short examples

*   Commit message with description and breaking change in body

        feat: allow provided config object to extend other configs

        BREAKING CHANGE: `extends` key in config file is now used for extending other config files

*   Commit message with no body

        docs: correct spelling of CHANGELOG

*   Commit message with scope

        feat(language): added russian language
    
*   Commit message for a fix using an (optional) issue number.

        fix: minor typos in code

        see the issue for details on the typos fixed

        fixes issue #12
