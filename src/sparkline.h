/* sparkline.h -- ASCII Sparklines header file
 * 微线图
 */

#ifndef __SPARKLINE_H
#define __SPARKLINE_H

/* A sequence is represented of many "samples" */
struct sample {
    double value;
    char *label;
};

struct sequence {
    int length;
    int labels;
    struct sample *samples;
    double min, max;
};

#define SPARKLINE_NO_FLAGS 0
#define SPARKLINE_FILL 1      /* Fill the area under the curve. */
#define SPARKLINE_LOG_SCALE 2 /* Use logarithmic scale. */

struct sequence *createSparklineSequence(void);
void sparklineSequenceAddSample(struct sequence *seq, double value, char *label);
void freeSparklineSequence(struct sequence *seq);
sds sparklineRenderRange(sds output, struct sequence *seq, int rows, int offset, int len, int flags);
sds sparklineRender(sds output, struct sequence *seq, int columns, int rows, int flags);

#endif /* __SPARKLINE_H */
