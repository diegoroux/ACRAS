# Contributing to ACRAS.

Thank you for taking the time! This document tries to make this as easy as possible!

## Issues

If you have any question about ACRAS, please open a [discussion](https://github.com/diegoroux04/ACRAS/discussions).

When filling an issue answer the following:
- What version of ACRAS are you using? (acras -v)
- What version of CRAS are you using? (cras_test_client --version)
- Steps to reproduce the issue.
- What did you expect to happen?
- What happened?

## Opening a Pull Request

Before you start, open a [discussion](https://github.com/diegoroux04/ACRAS/discussions) about the changes you wish to make.

- Create a fork and clone it.
- Do your changes.
- Sign the DCO.
- One commit per fix/change.
- Your commit message should have a prefix.
    - fix: Bug fixes.
    - feature: Add new feature.
    - docs: Changes to README, CONTRIBUTING.md or any similar file.
    - build: Changes to Makefile.
    - optimize: Optimizes the code.
    - core: Anything that might not be covered by the previous prefixes.
- Your commit message should be concise and summarize your changes.
    - If fixing an open issue reference the issue number (e.g fix: fixes #12).
- If needed you may add a short description.

## Sign the DCO.

It's required that contributors sign off all commits submitted to the project.
Take a minute and read the [Developer Certificate of Origin (DCO)](https://developercertificate.org/) and sign it:
`git commit -s`
or do it manually (it's important that your name and email match with your git config):
```
Commit message.

Signed-off-by: Your Name <yourgit@email.com>
```
If you haven't pushed your commit but forgot to sign the DCO, you can still sign with:
`git commit --amend -s`
