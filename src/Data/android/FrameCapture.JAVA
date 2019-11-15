package com.javaframecapture;

public class FrameCapture extends org.qtproject.qt5.android.bindings.QtActivity
{
    static final int REQUEST_CAPTURE_IMAGE = 1;

    void captureAnImage()
    {
        dispatchTakePictureIntent();
    }

    private void dispatchTakePictureIntent()
    {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

        // Ensure that there's a camera activity to handle the intent
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(takePictureIntent, REQUEST_CAPTURE_IMAGE);
        }
    }

    @Override
    protected static void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (resultCode == RESULT_OK && requestCode == REQUEST_CAPTURE_IMAGE) {
            Bundle extras = data.getExtras();
            Bitmap imageBitmap = (Bitmap) extras.get("data");
            int width = bitmap.getWidth();
            int height = bitmap.getHeight();
            int size = bitmap.getRowBytes() * bitmap.getHeight();
            ByteBuffer byteBuffer = ByteBuffer.allocate(size);
            bitmap.copyPixelsToBuffer(byteBuffer);
            byte[] byteArray = byteBuffer.array();
            imageCaptured(byteArray, width, height);
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    public static native void imageCaptured(byte[] buf, int width, int height);
}
