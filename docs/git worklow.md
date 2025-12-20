# ✅ Recommended Git Workflow (Safe & Clean)

This is a **battle-tested workflow** for solo development with a `dev` branch.

---

## 1️⃣ Day-to-day development workflow

### Work normally

```bash
git checkout dev
# edit code
git status
git add .
git commit -m "combat system: initial melee support"
git push origin dev
```

**Rule:**

> Commit early, commit often. Messages can be messy on `dev`.

This keeps you safe.

---

## 2️⃣ Before cleanup: create a safety tag (VERY important)

Before rewriting history:

```bash
git tag dev-pre-cleanup
git push origin dev-pre-cleanup
```

This is your **panic button**.

If anything goes wrong:

```bash
git reset --hard dev-pre-cleanup
```

---

## 3️⃣ Clean up history with interactive rebase

### Decide how many commits to clean

```bash
git log --oneline
```

Suppose you want to clean last 12 commits:

```bash
git rebase -i HEAD~12
```

---

### The rebase editor opens

Example:

```text
pick a1b2c3 initial combat code
pick d4e5f6 fix typo
pick f7g8h9 debug prints
pick 111aaa refactor damage
pick 222bbb remove debug
```

Change to:

```text
pick a1b2c3 combat system (final)
fixup d4e5f6 fix typo
fixup f7g8h9 debug prints
fixup 111aaa refactor damage
fixup 222bbb remove debug
```

Save and close.

---

### If Git stops (conflicts)

Git will say something like:

```
CONFLICT (content): Merge conflict in combat_system.c
Resolve conflicts, then run 'git rebase --continue'
```

Now:

```bash
# fix files
git add combat_system.c
git rebase --continue
```

Repeat until finished.

---

## 4️⃣ Force-push safely (only on dev)

History has changed → you must force push:

```bash
git push --force-with-lease origin dev
```

**Why `--force-with-lease`?**

* Safer than `--force`
* Refuses if someone else pushed

---

## 5️⃣ Optional: merge dev → main

Once dev is clean and stable:

```bash
git checkout main
git merge dev
git push origin main
```

---

# 🔁 Ongoing Best Practices

### 🔹 Use `dev` for experimentation

* messy commits OK
* frequent pushes OK

### 🔹 Clean history only:

* before major milestones
* before merging to `main`

### 🔹 Never rewrite history on shared branches (except solo dev)

---

## 📌 Quick Reference

| Task               | Command                       |
| ------------------ | ----------------------------- |
| Check rebase state | `git status`                  |
| Start cleanup      | `git rebase -i HEAD~N`        |
| Continue rebase    | `git rebase --continue`       |
| Abort rebase       | `git rebase --abort`          |
| Safety tag         | `git tag dev-pre-cleanup`     |
| Safe force push    | `git push --force-with-lease` |

---

## Why this workflow fits your project

* Solo developer ✔
* Long-running dev branch ✔
* Complex refactors (ECS, combat, effects) ✔
* Avoids losing work ✔
* Keeps `main` readable ✔
