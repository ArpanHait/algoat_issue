<!--
PR Title Guideline:
<Type>(<scope>): <Precise PR deliverable>
Examples:
  Feat(sorting): Add Ciura ShellSort algorithm
  Fix(python): Resolve GIL release issue in sort_inplace
  Perf(numerics): Vectorize Float16 bit-flip counting sort
  Docs(contributing): Update CMake presets instructions
-->

# Pull Request

## Description

<!-- Provide a clear summary of the changes you've made and the rationale behind them. -->

Fixes #<!-- ISSUE_NUMBER -->

---

## Type of Change

<!-- Please mark the relevant option(s) with an "x" -->

- [ ] `feat`: New algorithm, heuristic, or capability
- [ ] `fix`: Bug fix
- [ ] `perf`: Performance optimization
- [ ] `refactor`: Code refactoring without behavioral change
- [ ] `docs`: Documentation addition or update
- [ ] `enhance`: Incremental enhancement to existing feature
- [ ] `test`: New or updated tests
- [ ] `chore`: Build system, CI, dependencies, or tooling

---

## Implementation Details

<!--
Explain how you implemented the solution.
For algorithmic additions or modifications, please mention:
- Time Complexity (Best / Average / Worst):
- Space Complexity (Auxiliary):
- Stability / In-place guarantees:
-->

---

## Benchmarks & Performance Metrics (if applicable)

<!--
For performance optimizations or new algorithms, attach benchmark numbers comparing before/after or vs numpy/std::sort.
Optional: Attach benchmark plots, graphs, or flamegraphs below.
-->

| Benchmark / Dataset | Baseline | Proposed | Speedup |
| :--- | :--- | :--- | :--- |
| e.g., 1M Float16 Random | 4.2ms | 2.0ms | ~2.1x |

<!-- Attach any relevant benchmark plots/images here (optional) -->

---

## Dependencies

<!-- List any new dependencies, packages, or compiler feature requirements added (or "None") -->

---

## Testing & Verification

<!-- Describe the testing workflows executed -->

- [ ] C++ Unit Tests (`ctest --preset debug` or `ctest --test-dir build --output-on-failure`)
- [ ] Python Tests (`pytest tests/python/ -v`)
- [ ] Memory & UB Sanitizers (`cmake --preset asan`)
- [ ] Custom / Manual test script: `...`

---

## Developer Checklist

- [ ] My PR title follows `<Type>(<scope>): <Precise PR deliverable>`.
- [ ] My branch was created from `main` using an approved prefix (`feat/`, `fix/`, `perf/`, etc.).
- [ ] I have formatted my C++ code using `clang-format`.
- [ ] My code produces no new compiler warnings or static analysis issues (`clang-tidy`).
- [ ] I have added unit tests covering the new functionality or regression fix.
- [ ] I have updated documentation / docstrings where appropriate.
- [ ] My changes do not break existing functionality.

---

## Impact Assessment

- [ ] **Isolated**: Changes are localized and do not affect existing algorithm dispatch or public APIs.
- [ ] **Breaking / Affects Others**: Changes modify public APIs or dispatcher heuristics (explain below).

<!-- If breaking or wide-ranging impact, explain here -->

---

## Future Improvements

<!-- Note any potential follow-ups, edge-case optimizations, or future work -->

---

## Additional Notes

<!-- Any other context or details reviewers should be aware of -->

---

## Mentions (Optional)

<!-- Tag relevant reviewers or maintainers using @username -->
