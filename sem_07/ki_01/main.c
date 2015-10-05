#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum fields { LEFT, RIGHT };
enum action { TO_LEFT, TO_RIGHT, VACUUM, DONE};

struct environment {
	int left_dirty;
	int right_dirty;
	enum fields agent_position;
};

struct perception {
	enum fields cur_position;
	int left_dirty;
	int right_dirty;
};

struct environment ENV;

enum action
perform_action(struct perception *perc)
{
	if (perc->cur_position == LEFT) {
		if (perc->left_dirty) {
			return VACUUM;
		} else if (perc->right_dirty) {
			return TO_RIGHT;
		} else {
			return DONE;
		}
	} else if (perc->cur_position == RIGHT) {
		if (perc->right_dirty) {
			return VACUUM;
		} else if (perc->left_dirty) {
			return TO_LEFT;
		} else {
			return DONE;
		}
	}
}

void
update_environment(enum action ac)
{
	switch (ac) {
		case TO_RIGHT:
			ENV.agent_position = RIGHT;
			break;
		case TO_LEFT:
			ENV.agent_position = LEFT;
			break;
		case VACUUM:
			if (ENV.agent_position == LEFT) {
				ENV.left_dirty = 0;
			} else if (ENV.agent_position == RIGHT) {
				ENV.right_dirty = 0;
			}
			break;
		case DONE:
			printf("iam leaving this shit!\n");
			exit(1);
		default:
			printf("oh that should not happen!\n");
			exit(1);
	}
}

void
print_env(void)
{
	printf("left_dirty: %d\n", ENV.left_dirty);
	printf("right_dirty: %d\n", ENV.right_dirty);
	printf("agent_position: %d\n\n", ENV.agent_position);
}

int
main(int argc, const char *argv[])
{
	struct perception per;

	ENV.left_dirty = 1;
	ENV.right_dirty = 1;
	ENV.agent_position = LEFT;
	print_env();

	per.left_dirty = ENV.left_dirty;
	per.right_dirty = ENV.right_dirty;
	per.cur_position = ENV.agent_position;
	update_environment(perform_action(&per));
	print_env();

	per.left_dirty = ENV.left_dirty;
	per.right_dirty = ENV.right_dirty;
	per.cur_position = ENV.agent_position;
	update_environment(perform_action(&per));
	print_env();

	per.left_dirty = ENV.left_dirty;
	per.right_dirty = ENV.right_dirty;
	per.cur_position = ENV.agent_position;
	update_environment(perform_action(&per));
	print_env();

	return 0;
}
