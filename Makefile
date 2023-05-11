BAZELOPT       =
PROJECT_NAME   = cgraph


bazel-debug:
	# bazel run $(BAZELOPT) //:setup --config=debug -- bdist_wheel
	# mkdir -p dist
	# cp bazel-bin/setup.runfiles/$(PROJECT_NAME)/dist/*.whl ./dist

bazel-build:
	# bazel run $(BAZELOPT) //:setup --config=test -- bdist_wheel
	# mkdir -p dist
	# cp bazel-bin/setup.runfiles/$(PROJECT_NAME)/dist/*.whl ./dist

bazel-release:
	# bazel run $(BAZELOPT) //:setup --config=release -- bdist_wheel
	# mkdir -p dist
	# cp bazel-bin/setup.runfiles/$(PROJECT_NAME)/dist/*.whl ./dist

bazel-test:
	bazel test --test_output=all $(BAZELOPT) //... --config=test --spawn_strategy=local --color=yes

bazel-clean:
	bazel clean --expunge